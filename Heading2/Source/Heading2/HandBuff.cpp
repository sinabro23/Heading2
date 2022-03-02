// Fill out your copyright notice in the Description page of Project Settings.


#include "HandBuff.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHandBuff::AHandBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BuffFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BuffFX"));
	SetRootComponent(BuffFX);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Buff(TEXT("ParticleSystem'/Game/_MyContents/FX/P_KwangBuff.P_KwangBuff'"));

	if (PS_Buff.Succeeded())
	{
		BuffFX->SetTemplate(PS_Buff.Object);
	}

	//Weapon->SetCollisionProfileName(TEXT("NoCollsion"));
}

// Called when the game starts or when spawned
void AHandBuff::BeginPlay()
{
	Super::BeginPlay();
	
}

