// Fill out your copyright notice in the Description page of Project Settings.


#include "HPPotion.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"

// Sets default values
AHPPotion::AHPPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POTION"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/_MyContents/Assets/Potion_1.Potion_1'"));
	if (SM.Succeeded())
	{
		PotionMesh->SetStaticMesh(SM.Object);
	}

	PotionMesh->SetupAttachment(GetRootComponent());
	Trigger->SetupAttachment(PotionMesh);

	PotionMesh->SetCollisionProfileName(TEXT("Collectible"));
	Trigger->SetCollisionProfileName(TEXT("Collectible"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	
}

// Called when the game starts or when spawned
void AHPPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHPPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHPPotion::OnCharacterOverlapped);
}



void AHPPotion::OnCharacterOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->GetPotion();
		Destroy();
	}
}



