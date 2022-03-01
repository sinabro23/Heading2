// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 *  �ִϸ��̼ǰ� ���õ� ������ ��� Ŭ����
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackHit); //FOnAttackHit�� Ŀ����.
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
	void JumpToSection(int32 MontageSection);

	FName GetAttackMontageName(int32 MontageSection); // ���� ���� �־��ָ� �� ���ڿ� �´� ���� �̸�
private:
	UFUNCTION()
	void AnimNotify_AttackHit(); // �Լ� �̸� �԰����� 

public:
	FOnAttackHit OnAttackHit;
};
