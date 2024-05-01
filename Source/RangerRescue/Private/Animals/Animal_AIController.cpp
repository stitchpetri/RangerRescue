// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Animals\Animal_AIController.h"

#include "MainCharacter.h"
#include "Animals/Animal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

AAnimal_AIController::AAnimal_AIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

void AAnimal_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AAnimal* const animal = Cast<AAnimal>(InPawn))
	{
		if (UBehaviorTree* const tree = animal->GetBehaviorTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(tree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(tree);
		}
	}
}

void AAnimal_AIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(
		TEXT("Perception Component")));
		SightConfig->SightRadius = 1000.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 250.f;
		SightConfig->PeripheralVisionAngleDegrees = 70.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;


		GetPerceptionComponent()->SetDominantSense(*SightConfig-> GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAnimal_AIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense((*SightConfig));
		
	}
}

void AAnimal_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const Char = Cast<AMainCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
