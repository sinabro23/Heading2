// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "StatComponent.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindHP(class UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHPChanged.AddUObject(this, &UHPBarWidget::UpdateHP); // 브로드 캐스트 되면 우리가 만든 함수 실행되게
}

void UHPBarWidget::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HPBar->SetPercent(CurrentStatComp->GetHPRatio());
	}
}
