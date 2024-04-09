// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMode/MasterBuildable.h"

// Sets default values
AMasterBuildable::AMasterBuildable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Scene);
	BuildableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BuildableMesh->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void AMasterBuildable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterBuildable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

