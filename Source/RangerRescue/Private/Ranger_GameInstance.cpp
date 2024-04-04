// Fill out your copyright notice in the Description page of Project Settings.


#include "Ranger_GameInstance.h"

#include "SavingSystem/SaveManager.h"

void URanger_GameInstance::Init()
{
	Super::Init();

	USaveManager::Init();
}
