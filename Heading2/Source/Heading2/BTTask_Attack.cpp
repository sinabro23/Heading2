// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MainAIController.h"
#include "MainCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MainCharacter = Cast<AMainCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MainCharacter)
		return EBTNodeResult::Failed;

	MainCharacter->Attack();
	bIsAttacking = true;

	MainCharacter->OnAttackEnd.AddLambda([this]()
	{
		bIsAttacking = false;
	});

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
