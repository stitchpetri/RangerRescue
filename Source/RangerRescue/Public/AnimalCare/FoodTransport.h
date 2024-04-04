// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FocusInterface.h"
#include "GameFramework/Actor.h"
#include "FoodTransport.generated.h"

UCLASS()
class RANGERRESCUE_API AFoodTransport : public AActor, public IFocusInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodTransport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlayerFocus_Implementation() override;
	virtual bool isFocasable_Implementation() override;

};
