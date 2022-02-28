// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "MainCharacter.h"

AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
}