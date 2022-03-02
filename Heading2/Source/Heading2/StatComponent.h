// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChanged);
// 캐릭터에 붙여서 그 레벨에 맞는 HP, 공격력 같은 데이터를 들고 있을 것임
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
	virtual void InitializeComponent() override; // 새로 정의 추가했음
public:
	void SetLevel(int32 CurrentLevel); // 레벨에 따른 값들을 데이터매니져에서 가져올것.
	void SetHP(int32 NewHP); // 레벨에 따른 값들을 데이터매니져에서 가져올것. UI랑 묶이는 것들은 함수로 만들어서 사용
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
