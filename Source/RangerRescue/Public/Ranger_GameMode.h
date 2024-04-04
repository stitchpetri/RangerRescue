// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ranger_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class RANGERRESCUE_API ARanger_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//ARanger_GameMode();

	virtual void InitGameState() override;
	
};
