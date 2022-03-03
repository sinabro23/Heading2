// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "MainAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory); 

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentPawn)
		return EBTNodeResult::Failed; // AI PawnOwner를 가져오기 실패하면 실패리턴

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed; // 내브 시스템을 가져오기를 실패하면 실패리턴

	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		// FName("PatrolPos")는 에디터의 블랙보드에서 만든 변수의 이름, Vector 타입으로 만들었기때문에 SetValueAsVector
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolPos"), RandomLocation); 
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
