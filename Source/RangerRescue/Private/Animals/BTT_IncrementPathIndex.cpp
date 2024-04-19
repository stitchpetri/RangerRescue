// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTT_IncrementPathIndex.h"

#include "Animals/Animal.h"
#include "Animals/Animal_AIController.h"
#include "Animals/PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_IncrementPathIndex::UBTT_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTT_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// try and get ai controller

	if (auto* const Controller = Cast<AAnimal_AIController>(OwnerComp.GetAIOwner()))
	{
		//try and get animal
		if (auto* const Animal = Cast<AAnimal>(Controller->GetPawn()))
		{
			//try get blackboard
			if (auto* const BC = OwnerComp.GetBlackboardComponent())
			{
				//get number of patrol points and in adn max indices
				auto const NumOfPoints = Animal->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NumOfPoints -1;
				auto Index = BC->GetValueAsInt(GetSelectedBlackboardKey());

				// change direction if we are at the first or last index if in bidirectional mode
				if (bBiDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (Index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}
				// write new value of index to blackboard	
				BC->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++Index : --Index) % NumOfPoints);

				//finsh with sucess
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			
		}
	}
	return EBTNodeResult::Failed;
}
