// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomCharacter.h"

#include "Components/BoxComponent.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Nose = CreateDefaultSubobject<UBoxComponent>(TEXT("Nose"));
	Nose->SetupAttachment(this->GetMesh(), "head");

	Jaw = CreateDefaultSubobject<UBoxComponent>(TEXT("Jaw"));
	Jaw->SetupAttachment(this->GetMesh(), "head");

	Ear = CreateDefaultSubobject<UBoxComponent>(TEXT("Ear"));
	Ear->SetupAttachment(this->GetMesh(), "head");
	
	
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input


