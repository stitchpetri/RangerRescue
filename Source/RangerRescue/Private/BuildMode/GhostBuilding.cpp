// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMode/GhostBuilding.h"

// Sets default values
AGhostBuilding::AGhostBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostMesh"));
	SetRootComponent(ActorMesh);

}

// Called when the game starts or when spawned
void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGhostBuilding::DespawnGhost()
{
	BuildableClass = nullptr;
	GhostMesh = nullptr;
	bIsActive = false;
	
}

void AGhostBuilding::OnSpawn(TSubclassOf<AMasterBuildable> Class, UStaticMesh* Mesh)
{
	if (!bIsActive)
	{
		BuildableClass = Class;
		GhostMesh = Mesh;
		bIsActive = true;

		ActorMesh->SetStaticMesh(GhostMesh);
	}
}

// Called every frame
void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

