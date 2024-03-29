// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

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

	virtual void PostInitializeComponents() override; // 직접 선언했음, 모든 컴포넌트들이 초기화 되고 난 이후

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class UStatComponent* StatComponent; // 여기에 스탯관련것들 들어있음

	UPROPERTY(VisibleAnywhere, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	class UMainAnimInstance* AnimInstance; // BeginPlay에서 캐스팅해서 받아줄것.

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	class USoundCue* AttackSound;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* RightHandBuff;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* LeftHandBuff;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HPBarWidgetComponent;

	UPROPERTY()
	int32 AttackIndex = 0;

	UPROPERTY()
	bool bIsEkeyPressed = false;


public:
	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void Pitch(float Value);

	void Attack(); // 캐릭터에서 애님인스턴스에 접근해서 몽타주 틀어주게만들것임.
	void AttackCheck();
	FOnAttackEnd OnAttackEnd; // 어택 끝날때 BehaviorTree에 알려주기 위함

	void GetPotion();


	void EKey();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted); // 델리게이트 해서 몽타주끝나면 호출할 함수.
};
