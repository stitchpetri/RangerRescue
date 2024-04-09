// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreator/PlayerCharacterCreator.h"

#include "Components/BoxComponent.h"

#include "Kismet/GameplayStatics.h"

APlayerCharacterCreator::APlayerCharacterCreator()
{

	
}

void APlayerCharacterCreator::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(this);
}
