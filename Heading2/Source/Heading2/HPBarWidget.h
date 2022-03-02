// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEADING2_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindHP(class UStatComponent* StatComp);

	UFUNCTION()
	void UpdateHP();
private:
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* PB_HPBar; // 에디터에서 만든 프로그래스 바 이름 그대로해야지 바인드됨.

	TWeakObjectPtr<class UStatComponent> CurrentStatComp; //외부 클래스를 들고 있으니 생명주기가 어떻게 되는지 추적하기 힘드니 스마트포인터로
};
