// Fill out your copyright notice in the Description page of Project Settings.


#include "Targeting/TargettingNet.h"

#include "FocusInterface.h"
#include "RangerPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATargettingNet::ATargettingNet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(Net);
	Net = CreateDefaultSubobject<USphereComponent>(TEXT("Net"));
	

	Net->SetSphereRadius(SphereRadius);
}

// Called when the game starts or when spawned
void ATargettingNet::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<AActor*> ATargettingNet::GetTargetsInRange()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ARangerPlayerController* MyPlayerController = Cast<ARangerPlayerController>(PlayerController);
	TArray<AActor*> FreshTargetsInRange;
	
	
	TArray<AActor*> OverlappingActors;
	TArray<AActor*> TargetsInRange;
	Net->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->Implements<UFocusInterface>())
		{
			TargetsInRange.AddUnique(Actor);
			if (MyPlayerController->RecentlyTargeted.Contains(Actor))
			{
				
				FreshTargetsInRange.AddUnique(Actor);
			}
			
		}
		
	}
	if (FreshTargetsInRange.IsEmpty())
	{
		MyPlayerController->RecentlyTargeted.Empty();
		return TargetsInRange;
	}
	return FreshTargetsInRange;
}

// Called every frame
void ATargettingNet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

