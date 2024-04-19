// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeOfDay.generated.h"

class ADirectionalLight;

UCLASS()
class RANGERRESCUE_API ATimeOfDay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeOfDay();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults|References", meta=(AllowPrivateAccess="true"))
	ADirectionalLight* Sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults|References", meta=(AllowPrivateAccess="true"))
	ADirectionalLight* Moon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults|Time", meta=(AllowPrivateAccess="true",  ClampMin="0", ClampMax="24", SliderMin="0", SliderMax="24"))
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Defaults|Time", meta=(AllowPrivateAccess="true"))
	float TimeStep;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateSun();

	UFUNCTION(BlueprintCallable)
	void IncrementTime();

	bool bMoonVisible;

};
