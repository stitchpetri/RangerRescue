// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTT_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "Animals/Animal_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindRandomLocation::UBTT_FindRandomLocation(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const controller = Cast<AAnimal_AIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const animal = controller->GetPawn())
		{
			auto const Origin = animal->GetActorLocation();

			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
