// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"


void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		FVector SpeedSize = Pawn->GetVelocity();
		SpeedSize.Z = 0.f;
		Speed = SpeedSize.Size();
	}
}
