// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMainAIController::AMainAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/_MyContents/AI/BT_MainCharacter.BT_MainCharacter'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/_MyContents/AI/BB_MainCharacter.BB_MainCharacter'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

}

void AMainAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainAIController::RandomMove, 3.f, true);
	
	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{

		}
	}
}

void AMainAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMainAIController::RandomMove()
{
	//auto CurrentPawn = GetPawn();

	//UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	//if (nullptr == NavSystem)
	//	return;

	//FNavLocation RandomLocation;

	//if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("ACTOR : %s Moved"), *GetPawn()->GetName());
	//	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	//}
}
