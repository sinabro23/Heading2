// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchTarget.generated.h"

/**
 * 플레이어가 있으면 추적하는 기능을 BehaviorTree에 넣기 위해 만든 클래스 
 */
UCLASS()
class HEADING2_API UBTService_SearchTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SearchTarget();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
