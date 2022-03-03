// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MainAIController.h"
#include "MainCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f; // 틱 주기 설정
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentPawn)
		return;

	// OverlapMultiByChannel 인자들
	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;
	if (nullptr == World)
		return;
	TArray<FOverlapResult> OverlapResults; // 오버랩된 것들의 정보가 들어갈 자료구조
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn); // CurrentPawn은 나를 무시하기 위해 넣은 것

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams); // 오버랩 체크

	if (bResult) // 충돌값이 하나라도 있으면 True
	{
		for (auto& OverlapResult : OverlapResults)
		{
			AMainCharacter* MainCharacter = Cast<AMainCharacter>(OverlapResult.GetActor());
			if (MainCharacter && MainCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), MainCharacter);
				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}

		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);

		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
}