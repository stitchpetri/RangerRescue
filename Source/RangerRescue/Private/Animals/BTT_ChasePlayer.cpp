// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTT_ChasePlayer.h"

#include "Animals/Animal_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UBTT_ChasePlayer::UBTT_ChasePlayer(const FObjectInitializer& ObjectInitializer): UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Controller = Cast<AAnimal_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		//move to players location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
	
}
