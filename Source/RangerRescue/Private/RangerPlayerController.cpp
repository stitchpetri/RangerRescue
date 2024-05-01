// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerPlayerController.h"

#include "K2Node_SpawnActorFromClass.h"
#include "Targeting/TargettingNet.h"

AActor* ARangerPlayerController::Target()
{
	UWorld* World = GetWorld();
	if (World)
	{
		const APawn* Char = this->GetPawn();
		const FVector ForwardVector = Char->GetActorForwardVector();
		const float Distance = 100.0;
		const FVector NetSpawnLocation = Char->GetActorLocation() +  (ForwardVector * Distance);
		const FActorSpawnParameters SpawnParameters;

		ATargettingNet* TargettingNet = World->SpawnActor<ATargettingNet>(TargettingNetClass, NetSpawnLocation, FRotator::ZeroRotator, SpawnParameters);

		if (TargettingNet)
		{
			
			AActor* ClosestActor = GetClosestActor(TargettingNet->GetTargetsInRange()).Actor;
			
			FocusActor(ClosestActor);
			return ClosestActor;
		}
	}
	return nullptr;
}


FClosestActorResult ARangerPlayerController::GetClosestActor(TArray<AActor*> Actors)
{
	FClosestActorResult Result;
	Result.Actor = nullptr;
	Result.Distance = 50000.0f;
	
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
	if (CurrentTarget)
	{
		OnStoppedFocus(CurrentTarget);
		if(Targetter != nullptr)
		{
			Targetter->Destroy();
		}
		CurrentTarget = nullptr;
	}
	
	
}
