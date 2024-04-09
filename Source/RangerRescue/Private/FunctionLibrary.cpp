// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary.h"

#include "RangerPlayerController.h"

FVector UFunctionLibrary::SetCursorWorldPosition(ARangerPlayerController* PlayerController, float SightDistance)
{
	FHitResult HitResult;
	FVector CursorWorldLocation, CursorWorldDirection;
	
	if (PlayerController && PlayerController->DeprojectMousePositionToWorld(CursorWorldLocation, CursorWorldDirection))
	{
		FVector Start = CursorWorldLocation;
		FVector End = CursorWorldDirection*SightDistance + CursorWorldLocation;

		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());

		bool bHit = PlayerController->GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility,
			QueryParams
		);

		if (bHit && HitResult.GetActor() != nullptr)
		{
			return HitResult.Location;
		}
		
		
	}

	// Return a zero vector if the deprojection fails or if PlayerController is null.
	// This might signify an error or an invalid state.
	return FVector::ZeroVector;
}
