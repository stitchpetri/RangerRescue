// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTService_AdjustSpeed.h"

#include "Animals/Animal_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTService_AdjustSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AAIController* Controller = OwnerComp.GetAIOwner();
	const APawn* ControlledPawn = Controller ? Controller->GetPawn() : nullptr;
	if (!ControlledPawn) return;

	UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(ControlledPawn->GetMovementComponent());
	if (!MoveComp) return;

	const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	const float CurrentDistance = FVector::Dist(ControlledPawn->GetActorLocation(), TargetLocation);

	// Calculate speed based on distance
	const float NewSpeed = FMath::GetMappedRangeValueClamped(
		FVector2D(0.0f, SlowRadius), // Input range from 0 to SlowRadius
		FVector2D(MinSpeed, MaxSpeed), // Output range from MinSpeed to MaxSpeed
		CurrentDistance // The current distance which will be mapped
	);

	MoveComp->MaxWalkSpeed = NewSpeed;
}
