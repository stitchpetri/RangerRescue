// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TargettingNet.generated.h"

UCLASS()
class RANGERRESCUE_API ATargettingNet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargettingNet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
	float SphereRadius = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere")
	USphereComponent* Net;

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	TArray<AActor*> GetTargetsInRange();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
