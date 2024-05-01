// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryStatics.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYCRAFTING_API UInventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void PrintScreen(const FString& String, const FColor Color = FColor::Magenta, const float Time = 5.f);
};
