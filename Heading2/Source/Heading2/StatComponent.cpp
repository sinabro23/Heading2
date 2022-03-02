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

	Level = 1; // 나머지는 데이터 매니저에서 긁어서 사용할 것
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
	auto MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); // 월드세팅에서 데이터용으로 만들어놓은 게임인스턴스를 설정해 놨음. 그걸 가져오는것
	if (MainGameInstance)
	{
		auto StatData = MainGameInstance->GetStatData(CurrentLevel); // 레벨에 맞는 구조체의 정보들을 가져옴.
		{
			Level = StatData->Level;
			SetHP(StatData->MaxHP); // 렙업하면 체력 만피
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


