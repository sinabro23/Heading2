// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "MainAIController.h"
#include "MainCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == CurrentPawn)
        return false;

   auto Target = Cast<AMainCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
  
   if (nullptr == Target)
       return false;

   return bResult && Target->GetDistanceTo(CurrentPawn) <= 200.f;
}
