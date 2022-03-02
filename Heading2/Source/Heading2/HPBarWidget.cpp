// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "StatComponent.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindHP(class UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHPChanged.AddUObject(this, &UHPBarWidget::UpdateHP); // ��ε� ĳ��Ʈ �Ǹ� �츮�� ���� �Լ� ����ǰ�
}

void UHPBarWidget::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HPBar->SetPercent(CurrentStatComp->GetHPRatio());
	}
}
