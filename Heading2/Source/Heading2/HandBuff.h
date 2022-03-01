// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandBuff.generated.h"

UCLASS()
class HEADING2_API AHandBuff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* BuffFX;
};
