// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreator/PlayerCharacterCreator.h"

#include "Kismet/GameplayStatics.h"

void APlayerCharacterCreator::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(this);
}
