// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChanged);
// ĳ���Ϳ� �ٿ��� �� ������ �´� HP, ���ݷ� ���� �����͸� ��� ���� ����
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEADING2_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override; // ���� ���� �߰�����
public:
	void SetLevel(int32 CurrentLevel); // ������ ���� ������ �����͸Ŵ������� �����ð�.
	void SetHP(int32 NewHP); // ������ ���� ������ �����͸Ŵ������� �����ð�. UI�� ���̴� �͵��� �Լ��� ���� ���
	void OnAttacked(float DamageAmount);

	int32 GetLevel() { return Level; }
	int32 GetHP() { return HP; }
	int32 GetMaxHP() { return HP; }
	float GetHPRatio() { return HP / (float)(MaxHP); }
	int32 GetAttack() { return Attack; }


private:

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 HP;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHP;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

public:
	FOnHPChanged OnHPChanged;
		
};
