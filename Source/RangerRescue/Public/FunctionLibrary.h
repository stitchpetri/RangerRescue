// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

class ARangerPlayerController;


UCLASS()
class RANGERRESCUE_API UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

 public:

	UFUNCTION(BlueprintCallable)
	static FVector SetCursorWorldPosition(ARangerPlayerController* PlayerController, float SightDistance);
	
};
