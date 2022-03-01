// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class HEADING2_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override; // ���� ��������, ��� ������Ʈ���� �ʱ�ȭ �ǰ� �� ����
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	class UMainAnimInstance* AnimInstance; // BeginPlay���� ĳ�����ؼ� �޾��ٰ�.

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	class USoundCue* AttackSound;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* RightHandBuff;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* LeftHandBuff;

	UPROPERTY()
	int32 AttackIndex = 0;

	UPROPERTY()
	bool bIsEkeyPressed = false;

public:
	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void Pitch(float Value);

	void Attack(); // ĳ���Ϳ��� �ִ��ν��Ͻ��� �����ؼ� ��Ÿ�� Ʋ���ְԸ������.
	void AttackCheck();

	void EKey();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted); // ��������Ʈ �ؼ� ��Ÿ�ֳ����� ȣ���� �Լ�.
};
