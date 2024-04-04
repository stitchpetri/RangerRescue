// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerPlayerController.h"

#include "K2Node_SpawnActorFromClass.h"
#include "Targeting/TargettingNet.h"

void ARangerPlayerController::Target()
{
	UWorld* World = GetWorld();
	if (World)
	{
		const FActorSpawnParameters SpawnParameters;

		ATargettingNet* TargettingNet = World->SpawnActor<ATargettingNet>(ATargettingNet::StaticClass(), this->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);

		if (TargettingNet)
		{
			
			AActor* ClosestActor = GetClosestActor(TargettingNet->GetTargetsInRange()).Actor;
			
			ClearFocus();
			FocusActor(ClosestActor);
		}
	}
}


FClosestActorResult ARangerPlayerController::GetClosestActor(TArray<AActor*> Actors)
{
	FClosestActorResult Result;
	Result.Actor = nullptr;
	Result.Distance = 1000.0f;
	
	for (AActor* Actor : Actors)
	{
		const float DistanceTo = Actor->GetDistanceTo(GetPawn());
		if (DistanceTo < Result.Distance)
		{
			Result.Distance = DistanceTo;
			Result.Actor = Actor;
		}
	}
	
	return Result;
}

void ARangerPlayerController::FocusActor(AActor* Actor)
{
	if (Actor != nullptr)
	{
		CurrentTarget = Actor;

		RecentlyTargeted.AddUnique(Actor);

		const FActorSpawnParameters SpawnParameters;

		UWorld* World = GetWorld();
	
	
		Targetter = World->SpawnActor<AActor>(TargetterClass, CurrentTarget->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);

		if (Targetter)
		{
			Targetter->AttachToActor(CurrentTarget, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
	
	
}

void ARangerPlayerController::ClearFocus()
{
	CurrentTarget = nullptr;
	if(Targetter)
	{
		Targetter->Destroy();
	}
}
