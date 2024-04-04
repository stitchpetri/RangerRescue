// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCreator/CharacterCreator.h"
#include "PlayerCharacterCreator.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class RANGERRESCUE_API APlayerCharacterCreator : public ACharacterCreator
{
	GENERATED_BODY()
public:

	//APlayerCharacterCreator();
	
	virtual void BeginPlay() override;

protected:

	
};
