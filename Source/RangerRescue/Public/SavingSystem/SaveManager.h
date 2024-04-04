// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "RangerRescue/SaveMetadata.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class RANGERRESCUE_API USaveManager : public UObject
{
	GENERATED_BODY()
	
private:
	// The Current Save SLot 
	static FString CurrentSaveSlot;

	// all actors in the game that implement the save interface
	static TArray<TScriptInterface<ISaveInterface>> SaveInterfaces;

public:

	// Initializes the class must be called when game begins
	static void Init();

	//Queries all actors in the game that implement the save interface
	static void QueryAllSaveInterfaces();

	//Saves current state of the game 
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void SaveGame();

	// Loads current state of the game 
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void LoadGame();

	//Deletes Specified spot 
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void DeleteSlot(const FString& Slot);

	// Gets a new unused slot (new game)
	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static UPARAM(DisplayName = "Slot") FString GetNewSaveSlot(bool& Slot_Found);

	// sets current save slot to teh specified value
	UFUNCTION(BlueprintCallable, Category = "SavingAndLoading")
	static void SetCurrentSaveSlot(const FString& Slot);

	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static FString GetCurrentSaveSlot();

	//Gets all the saved games
	UFUNCTION(BlueprintPure, Category = "SavingAndLoading")
	static TArray<FSaveMetadata> GetAllSaveMetaData();

};
