// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;

	Level = 1; // �������� ������ �Ŵ������� �ܾ ����� ��
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UStatComponent::SetLevel(int32 CurrentLevel)
{
	auto MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); // ���弼�ÿ��� �����Ϳ����� �������� �����ν��Ͻ��� ������ ����. �װ� �������°�
	if (MainGameInstance)
	{
		auto StatData = MainGameInstance->GetStatData(CurrentLevel); // ������ �´� ����ü�� �������� ������.
		{
			Level = StatData->Level;
			SetHP(StatData->MaxHP); // �����ϸ� ü�� ����
			MaxHP = StatData->MaxHP;
			Attack = StatData->Attack;
		}
	}
}

void UStatComponent::SetHP(int32 NewHP)
{
	HP = NewHP;
	if (HP < 0)
		HP = 0;

	OnHPChanged.Broadcast();
}

void UStatComponent::OnAttacked(float DamageAmount)
{
	int NewHP = HP - DamageAmount;
	SetHP(NewHP);
}


