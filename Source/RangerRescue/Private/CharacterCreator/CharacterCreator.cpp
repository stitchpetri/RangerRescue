// Fill out your copyright notice in the Description page of Project Settings.



#include "CharacterCreator/CharacterCreator.h"

#include "AssetDefinition.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "Character/CustomCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Iris/ReplicationSystem/RepTag.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Widgets/Images/SImage.h"

// Sets default values
ACharacterCreator::ACharacterCreator()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	CharacterSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterSpawnLocation"));
	CharacterSpawnLocation->SetupAttachment(SceneRoot);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SceneRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	

}


void ACharacterCreator::BeginPlay()
{
	Super::BeginPlay();
// spawn the actor in bluprints and assign variable
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);

	
	
}



void ACharacterCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isRotatingCamera && !isSettingSkinTint)
	{
		CameraRotationUpdate(DeltaTime);
	}
	else
	{
		if (isManipulating && !isSettingSkinTint)
		{
			ManipulateUpdate(DeltaTime);
		}
	}

	HighlightUpdate();

}

void ACharacterCreator::InteractUpdate(float DeltaSeconds)
{
	
	CameraRotationUpdate(DeltaSeconds);

	//Manipulate();
	
}


void ACharacterCreator::Zoom(float Amount)
{
	const float CurrentLength = SpringArm->TargetArmLength;
	SpringArm->TargetArmLength = FMath::Clamp(CurrentLength + (Amount*ZoomSpeed), MinZoom, MaxZoom);
}

void ACharacterCreator::CameraRotationUpdate(float DeltaTime) const
{
	const float CurrentYaw = SpringArm->GetComponentRotation().Yaw;
	const float NewYaw = DeltaTime*MouseSpeed*MouseX + CurrentYaw;

	const float CurrentPitch = SpringArm->GetComponentRotation().Pitch;
	const float NewPitch = DeltaTime*MouseSpeed*MouseY + CurrentPitch;
	
	SpringArm->SetWorldRotation(FRotator(NewPitch,NewYaw,0.0));
}

void ACharacterCreator::StartInteract()
{
	if (CurrentManipulation != "")
	{
		isManipulating = true;
		CheckforDepth();
		
	}
	else
	{
		isRotatingCamera = true;
	}
	
}

void ACharacterCreator::StopInteract()
{
	isRotatingCamera = false;
	isManipulating = false;
	CurrentManipulation = "";
	isSettingSkinTint = false;
	isSettingHairTint = false;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// Set input mode to game and UI
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false); // Set to true if you want to hide the cursor
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
}

void ACharacterCreator::CheckforDepth() 
{
	if (Character == nullptr) { return; } // Corrected return statement
    
	const FVector CameraForward = Camera->GetForwardVector();
	const FVector ActorVector = Character->GetActorRightVector() * -1;
    
	// Ensure the dot product is clamped to prevent potential acos issues.
	const float DotValue = FMath::Clamp(FVector::DotProduct(CameraForward, ActorVector), -1.0f, 1.0f);
	const float AngleDegrees = FMath::RadiansToDegrees(acos(DotValue));
    
	if (AngleDegrees > 40.0f)
	{
		isManipulatingDepth = true;
		

		const FVector NewCameraForward = Camera->GetForwardVector();
		const FVector ActorVectorForward = Character->GetActorForwardVector();
    
		// -1 to the left of character +1 to the right 
		const float NewDotValue = FMath::Clamp(FVector::DotProduct(NewCameraForward, ActorVectorForward), -1.0f, 1.0f);

		if(NewDotValue < 0.0)
		{
			isManipulatingDepthFromRight = true;
		}
		if (NewDotValue >= 0.0)
		{
			isManipulatingDepthFromRight = false;
		}
		
		

		
	}
	else
	{
		isManipulatingDepth = false;
		
	}
}


void ACharacterCreator::HighlightUpdate()
{

	if (isManipulating) {return;}
		
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;
	
	
	FVector MouseLocation, MouseDirection;
	if (PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
	{
		FVector Start = MouseLocation;
		FVector End = Start + (MouseDirection * 10000);

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_Visibility,
				FCollisionQueryParams(),
				FCollisionResponseParams()
			);

		if (bHit && HitResult.Component.IsValid())
		{
			FString HitComponentName = HitResult.Component->GetName();

			if (HitComponentName == "Nose")
			{
				CurrentManipulation = HitComponentName;

				SetHighlightParams("HighlightID", 0);
				SetHighlightParams("HighlightOn", 1);
			}
			else if (HitComponentName == "Jaw")
			{
				CurrentManipulation = HitComponentName;

				SetHighlightParams("HighlightID", 1);
				SetHighlightParams("HighlightOn", 1);
			}
			else if (HitComponentName == "Ear")
			{
				CurrentManipulation = HitComponentName;
				SetHighlightParams("HighlightID", 2);
				SetHighlightParams("HighlightOn", 1);
			}
			else if (HitComponentName == "Crest")
			{
				CurrentManipulation = HitComponentName;
				SetHighlightParams("HighlightID", 1);
				SetHighlightParams("HighlightOn", 1);
			}
			else
			{
				// If the component hit is not one we're interested in, treat it as a request to rotate the camera.
				CurrentManipulation = "";
				//isRotatingCamera = true;
				SetHighlightParams("HighlightOn", 0);
			}
		}
		else
		{
			SetHighlightParams("HighlightOn", 0);
			CurrentManipulation = "";
		}
		
		
		
	}
}

void ACharacterCreator::SkinTintUpdate(UImage* Picker, float DeltaSeconds)
{
	SkinTintCoordinates.X = FMath::Clamp(SkinTintSpeed*DeltaSeconds*MouseX + SkinTintCoordinates.X, 0.0, 127.0);
	SkinTintCoordinates.Y = FMath::Clamp((SkinTintSpeed*DeltaSeconds*(-MouseY) + SkinTintCoordinates.Y), 0.0, 127.0);;

	FWidgetTransform WidgetTransform;
	WidgetTransform.Translation = SkinTintCoordinates;
	Picker->SetRenderTransform(WidgetTransform);

	SetVectorParam("SkinTint", SkinTintCoordinates);
}

void ACharacterCreator::HairTintUpdate(UImage* Picker, float DeltaSeconds)
{
	HairTintCoordinates.X = FMath::Clamp(SkinTintSpeed*DeltaSeconds*MouseX + HairTintCoordinates.X, 0.0, 127.0);
	HairTintCoordinates.Y = FMath::Clamp((SkinTintSpeed*DeltaSeconds*(-MouseY) + HairTintCoordinates.Y), 0.0, 127.0);;

	FWidgetTransform WidgetTransform;
	WidgetTransform.Translation = HairTintCoordinates;
	Picker->SetRenderTransform(WidgetTransform);

	SetVectorParam("HairTint", HairTintCoordinates);
}



