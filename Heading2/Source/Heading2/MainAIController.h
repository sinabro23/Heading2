// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MainAIController.generated.h"

/**
 * 
 */
UCLASS()
class HEADING2_API AMainAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMainAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	FTimerHandle TimerHandle;

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;

	// blackboardcomponent는 기본적으로 들어있음 BlackBoard라는 이름으로
private:
	void RandomMove();

};
