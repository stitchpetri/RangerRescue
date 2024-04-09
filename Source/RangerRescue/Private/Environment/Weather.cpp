// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Weather.h"

#include "Components/PostProcessComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeather::AWeather()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AWeather::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AWeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	const float InterpSpeed = 0.05f; // Adjust interpolation speed as needed
	const FLinearColor NewRayScattering = UKismetMathLibrary::CInterpTo(CurrentRayleighScatteringColor, TargetRayleighScatteringColor, DeltaTime, InterpSpeed);
	const float NewDensity = (CurrentCloudDensityOffset, TargetCloudDensityOffset, DeltaTime, InterpSpeed); // Adjust the range as needed
	const float NewExposureComp = FMath::FInterpTo(CurrentExposureCompensation , TargetExposureCompensation, DeltaTime, InterpSpeed); // Adjust the range as needed

	// Set the new values
	SetAtmosphereValues(NewRayScattering, NewDensity, NewExposureComp);

	// Example of using Clamp with IsNearlyEqual
	if (FMath::IsNearlyEqual(CurrentExposureCompensation, TargetExposureCompensation, 0.05f))
	{
		SetActorTickEnabled(false);
	}
	else
	{
		SetActorTickEnabled(true);
	}
	
	
}

void AWeather::SetAtmosphereValues(FLinearColor RayleighScattering, float DensityOffset, float ExposureCompensation)
{
	if (SkyAtmosphere == nullptr || VolumetricCloud == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("You need to set the default values in BP Weather"));
		return;
	}
    
	SkyAtmosphere->SetRayleighScattering(RayleighScattering);
    
	// Only create a new dynamic material instance if it hasn't been created yet
	if (CloudMaterial == nullptr)
	{
		if (VolumetricCloudMaterial != nullptr)
		{
			
			CloudMaterial = UMaterialInstanceDynamic::Create(VolumetricCloudMaterial, this);
			if (CloudMaterial != nullptr)
			{
				VolumetricCloud->SetMaterial(CloudMaterial);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to create CloudMaterial"));
				return;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VolumetricCloud->Material is nullptr"));
			return;
		}
	}
	if (PostProcess != nullptr)
	{
		// Enable the override for the exposure compensation setting.
		PostProcess->Settings.bOverride_AutoExposureBias = true;

		// Set the exposure compensation value.
		PostProcess->Settings.AutoExposureBias = ExposureCompensation;
	}
	CurrentExposureCompensation = ExposureCompensation;
    CurrentCloudDensityOffset = DensityOffset;
	CurrentRayleighScatteringColor = RayleighScattering;
	CloudMaterial->SetScalarParameterValue(FName("DensityOffset"), DensityOffset);
	SetActorTickEnabled(true);
}

void AWeather::SetAtmosphereParameters(FLinearColor Color, float DensityOffset, float ExposureCompensation)
{
	TargetCloudDensityOffset = DensityOffset;
	TargetExposureCompensation = ExposureCompensation;
	TargetRayleighScatteringColor = Color;
}







