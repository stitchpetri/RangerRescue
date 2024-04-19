// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTT_FindPathPoint.h"

#include "Animals/Animal.h"
#include "Animals/Animal_AIController.h"
#include "Animals/PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindPathPoint::UBTT_FindPathPoint(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName= TEXT("Find Path Point");
}

EBTNodeResult::Type UBTT_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Controller = Cast<AAnimal_AIController>(OwnerComp.GetAIOwner()))
	{
		// get blackbaord component from the behavior tree
		if (auto* const bb = OwnerComp.GetBlackboardComponent())
		{
			// get current patrol index from blackboard
			auto const index = bb->GetValueAsInt(GetSelectedBlackboardKey());

			// get animal
			if (auto* animal = Cast<AAnimal>(Controller->GetPawn()))
			{
				// get current patrol path vector fro the animal - local to the patrol path actor
				auto const Point = animal->GetPatrolPath()->GetPatrolPoint(index);

				//convert to world space
				auto const GlobalPoint = animal->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
				bb->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				//finish
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
