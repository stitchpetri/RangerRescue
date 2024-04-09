// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weather.generated.h"

class UPostProcessComponent;
class UVolumetricCloudComponent;

UCLASS()
class RANGERRESCUE_API AWeather : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeather();

	UFUNCTION(BlueprintCallable)
	void SetAtmosphereValues(FLinearColor Color, float DensityOffset, float ExposureCompensation);

	UFUNCTION(BlueprintCallable)
	void SetAtmosphereParameters(FLinearColor Color, float DensityOffset, float ExposureCompensation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	UVolumetricCloudComponent* VolumetricCloud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	UPostProcessComponent* PostProcess;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
	UMaterialInstance* VolumetricCloudMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	float CurrentCloudDensityOffset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	float TargetCloudDensityOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	float CurrentExposureCompensation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	float TargetExposureCompensation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	FLinearColor CurrentRayleighScatteringColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtmosphereValues")
	FLinearColor TargetRayleighScatteringColor;
	
	UMaterialInstanceDynamic* CloudMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
