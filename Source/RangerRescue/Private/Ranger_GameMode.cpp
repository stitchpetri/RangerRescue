// Fill out your copyright notice in the Description page of Project Settings.


#include "Ranger_GameMode.h"

#include "SavingSystem/SaveManager.h"

void ARanger_GameMode::InitGameState()
{
	Super::InitGameState();
	
	USaveManager::QueryAllSaveInterfaces();
	USaveManager::LoadGame();
	
	
}
