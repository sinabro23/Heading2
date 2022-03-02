// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MainGameInstance.generated.h"

/**
 *  ���� ������ Ŭ���� GameInstance :  ���� ���� �� �����Ǹ� ���� �ν��Ͻ��� ����� ������ �Ҹ���� �ʽ��ϴ�. 
 */

USTRUCT() // �̷��� ���� ����ü�� �����Ϳ��� ������ ���̺� ���鶧 ������ �� ����
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
