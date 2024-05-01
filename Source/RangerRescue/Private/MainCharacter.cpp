// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"



#include "BuildMode/BuildModePawn.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	ThirdPersonCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SetupStimulusSource();
	
	//Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void AMainCharacter::OnBeforeSave_Implementation()
{
	// blueprint
	
}

FString AMainCharacter::GetUniqueSaveName_Implementation()
{
	FString Name = "Player";
	return Name;
}


// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerCameraManager* const camMan = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	camMan->ViewPitchMin = ViewPitchMin;
	camMan->ViewPitchMax = ViewPitchMax;
	
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (CurveFloatAsset)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		FocusTimeline.AddInterpFloat(CurveFloatAsset, TimelineProgress);

		FocusTimeline.SetLooping(false);
		FocusTimeline.SetTimelineLength(1.0f); // Example duration of 5 seconds, adjust as needed
		UE_LOG(LogTemp, Warning, TEXT("Timeline setup completed."));
	}
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FocusTimeline.TickTimeline(DeltaTime);
}

void AMainCharacter::SetupStimulusSource()
{
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterWithPerceptionSystem();
	}
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}// input is a Vector2D
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		
		
	}
}

void AMainCharacter::Focus(const FInputActionValue& Value)
{
	if (CurveFloatAsset)
	{
		FocusTimeline.PlayFromStart();
	}
}

void AMainCharacter::EndFocus(const FInputActionValue& Value)
{
	if (CurveFloatAsset)
	{
		
		FocusTimeline.Reverse();
	}
}

void AMainCharacter::TimelineProgress(float Value)
{
	float NewLength = FMath::Lerp(NormalSpringArmLength, FocusSpringArmLength, Value);
	CameraBoom->TargetArmLength = NewLength;
}

void AMainCharacter::OpenBuildMode()
{
	if (BuildModePawn != nullptr)
	{
		this->GetController()->Possess(BuildModePawn);
		bInBuildMode = true;
	}
	
}

void AMainCharacter::CloseBuildMode()
{
	this->GetController()->Possess(this);
	bInBuildMode = false;
}



// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		// Focus
		EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Started, this, &AMainCharacter::Focus);
		EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Completed, this, &AMainCharacter::EndFocus);
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

