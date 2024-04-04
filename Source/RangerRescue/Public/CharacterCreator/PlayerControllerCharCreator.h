// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerCharCreator.generated.h"

class ACharacterCreator;
/**
 * 
 */
UCLASS()
class RANGERRESCUE_API APlayerControllerCharCreator : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "References")
	ACharacterCreator* CharacterCreator;
	
};
