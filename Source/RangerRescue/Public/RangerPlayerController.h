// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RangerPlayerController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FClosestActorResult
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	AActor* Actor;

	UPROPERTY(BlueprintReadOnly)
	float Distance;
};

UCLASS()
class RANGERRESCUE_API ARangerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> RecentlyTargeted;

protected:

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	AActor* Target();

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	FClosestActorResult GetClosestActor(TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	void FocusActor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category = "Targetting")
	void ClearFocus();

	UFUNCTION(BlueprintImplementableEvent, Category = "Targetting")
	void OnStoppedFocus(AActor* Target);
	

	AActor* Targetter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Targetting")
	AActor* CurrentTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targetting")
	UClass* TargetterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<class ATargettingNet> TargettingNetClass;
};
