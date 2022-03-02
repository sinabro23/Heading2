// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("DataTable'/Game/_MyContents/Data/StatData.StatData'"));
    
    Stats = DataTable.Object; // 데이터 없으면 크래쉬 내기 위해 예외체크 안함.
}

void UMainGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"), GetStatData(1)->Attack);
}

FMainCharacterData* UMainGameInstance::GetStatData(int32 CurrentLevel)
{
    return Stats->FindRow<FMainCharacterData>(*FString::FromInt(CurrentLevel), TEXT(""));
}
