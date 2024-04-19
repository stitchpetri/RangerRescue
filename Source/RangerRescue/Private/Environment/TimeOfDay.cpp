// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/TimeOfDay.h"

#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"


// Sets default values
ATimeOfDay::ATimeOfDay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ATimeOfDay::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ATimeOfDay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimeOfDay::UpdateSun()
{
	if (Sun)
	{
		const float NewSunPitch = 90-Time*(360/24);
		Sun->SetActorRotation(FRotator(NewSunPitch, 0.0, 0.0));
	}
	
}

void ATimeOfDay::IncrementTime()
{
	Time = FMath::Fmod(Time+TimeStep, 24.0f);
	UpdateSun();
	if(Moon == nullptr){return;}

	if (Time > 18.0f || Time < 6.0f)
	{
		if (bMoonVisible != true)
		{
			Moon->GetLightComponent()->SetVisibility(true);
			bMoonVisible = true;
		}
		
	}
	else
	{
		if (bMoonVisible != false)
		{
			Moon->GetLightComponent()->SetVisibility(false);
			bMoonVisible = false;
		}
	}
}
