// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostBuilding.generated.h"

class AMasterBuildable;

UCLASS()
class RANGERRESCUE_API AGhostBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DespawnGhost();
	
	UFUNCTION(BlueprintCallable)
	void OnSpawn(TSubclassOf<class AMasterBuildable> Class, UStaticMesh* Mesh);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default|BuildingInfo")
	TSubclassOf<class AMasterBuildable> BuildableClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default|BuildingInfo")
	UStaticMesh* GhostMesh;

	bool bIsActive;

	UStaticMeshComponent* ActorMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
