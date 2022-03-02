// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MainGameInstance.generated.h"

/**
 *  스탯 관리용 클래스 GameInstance :  게임 생성 시 생성되며 게임 인스턴스가 종료될 때까지 소멸되지 않습니다. 
 */

USTRUCT() // 이렇게 만든 구조체는 에디터에서 데이터 테이블 만들때 참조할 수 있음
struct FMainCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;
};

UCLASS()
class HEADING2_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMainGameInstance();

	virtual void Init() override;

	FMainCharacterData* GetStatData(int32 CurrentLevel);

private:

	UPROPERTY()
	class UDataTable* Stats;

	
};
