// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 *  애니메이션과 관련된 정보를 담는 클래스
 */
UCLASS()
class HEADING2_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMainAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

public:
	void PlayAttackMontage();
};
