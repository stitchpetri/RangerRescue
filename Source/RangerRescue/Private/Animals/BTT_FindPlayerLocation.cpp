// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTT_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTT_FindPlayerLocation::UBTT_FindPlayerLocation(FObjectInitializer const& ObjectInitializer): UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTT_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		// get player location as an origin point
		auto const PlayerLocation = Player->GetActorLocation();
		if (SearchRadius)
		{
			FNavLocation Loc;

			// get nav system and generate a random location near the player
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
