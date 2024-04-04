// Fill out your copyright notice in the Description page of Project Settings.

#include "SavingSystem/SaveManager.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"
#include "SavingSystem/SaveGameData.h"
#include "SavingSystem/SaveGameMetadata.h"

static const int32 kMaxSaveSlots = 100;
static const FString kMetadataSaveSlot = "SaveGameMetadata";
FString USaveManager::CurrentSaveSlot;
TArray<TScriptInterface<ISaveInterface>> USaveManager::SaveInterfaces;


void USaveManager::Init()
{
	CurrentSaveSlot = "Default";

	// make sure metadata file exists if the game has not been ran
	const USaveGame* SaveGameMetadata = UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0);
	if (SaveGameMetadata == nullptr)
	{
		// metafile does not exist so create empty one
		USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(USaveGameMetadata::StaticClass());

		UGameplayStatics::SaveGameToSlot(SaveGameObject, kMetadataSaveSlot, 0);
	}
}

void USaveManager::QueryAllSaveInterfaces()
{
	//clear old entries
	SaveInterfaces.Empty();
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, USaveInterface::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		SaveInterfaces.Add(actor);
	}
}
void USaveManager::SaveGame()
{
	// Create new save game data instance
	USaveGameData* SaveGameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));

	// Go over all actors that need to be saved and save them
	for (auto& saveInterface : SaveInterfaces)
	{
		if (saveInterface.GetObject() == nullptr)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("SaveInterface Object is nullptr!"));
			continue;
		}

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("SaveInterface Object: %s"), *saveInterface.GetObject()->GetName()));

		// Let object know that it is about to be saved
		saveInterface->Execute_OnBeforeSave(saveInterface.GetObject());
		FString UniqueSaveName = saveInterface->Execute_GetUniqueSaveName(saveInterface.GetObject());
		FSaveData& saveData = SaveGameData->SerializedData.Add(UniqueSaveName);

		// Create memory writer
		FMemoryWriter MemoryWriter(saveData.Data);
		MemoryWriter.ArIsSaveGame = true;

		// Serialize object data
		saveInterface.GetObject()->Serialize(MemoryWriter);
	}

	// Save game to the current slot
	UGameplayStatics::SaveGameToSlot(SaveGameData, CurrentSaveSlot, 0);

	// Update metadata file with new slot
	USaveGameMetadata* SaveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));
	FSaveMetadata& SaveMetadata = SaveGameMetadata->SavedGamesMetadata.FindOrAdd(CurrentSaveSlot);
	SaveMetadata.SlotName = CurrentSaveSlot;
	SaveMetadata.Date = FDateTime::Now();

	// Save the changes to the metadata file
	UGameplayStatics::SaveGameToSlot(SaveGameMetadata, kMetadataSaveSlot, 0);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, "Saved: " + CurrentSaveSlot);
}

void USaveManager::LoadGame()
{
	USaveGame* LoadedData = UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0);
	UE_LOG(LogTemp, Warning, TEXT("Attempting to load save game from slot: %s"), *CurrentSaveSlot);
	 USaveGameData* SaveGameData = Cast<USaveGameData>(LoadedData);

	if (LoadedData != nullptr && SaveGameData == nullptr)
	{
		// This means the data was loaded, but it's not of USaveGameData type
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Data loaded, but casting to USaveGameData failed. Potential class mismatch."));
        
		// Optionally, handle the situation, e.g., by forcing a save to reset to the correct type
		SaveGame();
        
		// Re-attempt loading after addressing the casting issue
		SaveGameData = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));
	}
	else if (SaveGameData == nullptr)
	{
		// No data exists for the current slot, so save a default one
		SaveGame();
        
		// Reload it
		SaveGameData = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));
	}

	if (SaveGameData != nullptr)
	{
		// Successfully loaded and cast, now load your game data
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Loaded: ") + CurrentSaveSlot);
	}
	else
	{
		// Handle failure to load or cast
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Failed to load or cast save data."));
	}


	for (auto& saveInterface : SaveInterfaces)
	{
		if (saveInterface.GetObject() == nullptr)
			continue;

		//find unique name and save data
		FString UniqueSaveName = saveInterface->Execute_GetUniqueSaveName(saveInterface.GetObject());
		FSaveData* saveData = SaveGameData->SerializedData.Find(UniqueSaveName);
		if (saveData == nullptr)
			continue;
		// Deserialize the objects save data
		FMemoryReader MemoryReader(saveData->Data);
		MemoryReader.ArIsSaveGame = false;

		saveInterface.GetObject()->Serialize(MemoryReader);
	}
}

void USaveManager::DeleteSlot(const FString& Slot)
{
	UGameplayStatics::DeleteGameInSlot(Slot, 0);

	// loading the meta data file
	USaveGameMetadata* SaveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	SaveGameMetadata->SavedGamesMetadata.Remove(Slot);

	// save the metadata slot
	UGameplayStatics::SaveGameToSlot(SaveGameMetadata, kMetadataSaveSlot, 0);
}

FString USaveManager::GetNewSaveSlot(bool& Slot_Found)
{
	Slot_Found = false;

	// loading the meta data file
	const USaveGameMetadata* SaveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	for (int32 i = 0; i <kMaxSaveSlots; ++i)
	{
		//Save slot 1, 2 ...
		FString SlotName = "Save Slot " + FString::FromInt(i);

		if (SaveGameMetadata->SavedGamesMetadata.Contains(SlotName) == false)
		{
			// found a free slot
			Slot_Found = true;
			return SlotName;
		}
	}

	return FString();
}

void USaveManager::SetCurrentSaveSlot(const FString& Slot)
{
	CurrentSaveSlot = Slot;
}

FString USaveManager::GetCurrentSaveSlot()
{
	return CurrentSaveSlot;
}

TArray<FSaveMetadata> USaveManager::GetAllSaveMetaData()
{
	TArray<FSaveMetadata> Metadata;

	// loading the meta data file
	USaveGameMetadata* SaveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(kMetadataSaveSlot, 0));

	Metadata.Reserve(SaveGameMetadata->SavedGamesMetadata.Num());

	// add each saved games metadata to the return array

	for (const auto& saved_game : SaveGameMetadata->SavedGamesMetadata)
	{
		Metadata.Push(saved_game.Value);
	}
	return Metadata;
}
