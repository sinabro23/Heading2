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
	class UProgressBar* PB_HPBar; // �����Ϳ��� ���� ���α׷��� �� �̸� �״���ؾ��� ���ε��.

	TWeakObjectPtr<class UStatComponent> CurrentStatComp; //�ܺ� Ŭ������ ��� ������ �����ֱⰡ ��� �Ǵ��� �����ϱ� ����� ����Ʈ�����ͷ�
};
