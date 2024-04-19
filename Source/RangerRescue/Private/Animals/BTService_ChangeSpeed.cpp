// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/BTService_ChangeSpeed.h"

#include "AIController.h"
#include "Animals/Animal.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (auto const Cont = OwnerComp.GetAIOwner())
	{
		if (auto* const Animal = Cast<AAnimal>(Cont->GetPawn()))
		{
			Animal->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}
}
