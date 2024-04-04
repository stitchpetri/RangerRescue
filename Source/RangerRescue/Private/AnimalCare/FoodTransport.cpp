// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalCare/FoodTransport.h"

// Sets default values
AFoodTransport::AFoodTransport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodTransport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodTransport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodTransport::OnPlayerFocus_Implementation()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Focusing on food transport object"));
}

bool AFoodTransport::isFocasable_Implementation()
{
	return true;
}



