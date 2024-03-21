// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildMode/BuildModePawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetMathLibrary.h"

class UEnhancedInputLocalPlayerSubsystem;
// Sets default values
ABuildModePawn::ABuildModePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(GetRootComponent());

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnStaticMesh"));
	PawnMesh->SetupAttachment(Scene);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(PawnMesh);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	
	BuildModeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BuildModeCamera"));
	BuildModeCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	BuildModeCamera->bUsePawnControlRotation = false; // Cam

}

// Called when the game starts or when spawned
void ABuildModePawn::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void ABuildModePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABuildModePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABuildModePawn::Move);

		//Zoom
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ABuildModePawn::Zoom);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &ABuildModePawn::Zoom);

	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}


}

void ABuildModePawn::Move(const FInputActionValue& Value)
{
	if (DisableCamNav) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const float MoveSpeed = MovementSpeedCalculation() * FastMoveMultiplier;

	// Assuming X input is left/right and Y input is forward/backward.
	// Transform the 2D movement vector from pawn's local space to world space.
	const FVector ForwardVector = GetActorForwardVector() * MovementVector.Y;
	const FVector RightVector = GetActorRightVector() * MovementVector.X;

	// Combine the vectors for full movement direction and apply speed.
	const FVector MovementDirection = (ForwardVector + RightVector) * MoveSpeed;

	// Calculate the new location. No need to manually handle rotation or scale here.
	const FVector NewLocation = GetActorLocation() + MovementDirection;

	// Set the new location. This keeps the pawn's current rotation and scale unchanged.
	SetActorLocation(NewLocation);
}

void ABuildModePawn::Pan(const FInputActionValue& Value)
{
}

void ABuildModePawn::Zoom(const FInputActionValue& Value) 
{
	UE_LOG(LogTemp, Warning, TEXT("Zoom Value: %f"), Value.Get<float>());
	if (DisableCamNav == false)
	{
		const float ZoomValue = Value.Get<float>();
		if (ZoomValue > 0.0)
		{
			const float NewLength = CameraBoom->TargetArmLength - ZoomSensitivity;
			CameraBoom->TargetArmLength = FMath::Clamp(NewLength, 500, MaxArmDistance);

			UE_LOG(LogTemp, Warning, TEXT("ZoomValue: %f, NewLength: %f, TargetArmLength: %f"), ZoomValue, NewLength, CameraBoom->TargetArmLength);
		}
		else if (ZoomValue < 0.0 )
		{
			const float NewLength = CameraBoom->TargetArmLength + ZoomSensitivity;
			CameraBoom->TargetArmLength = FMath::Clamp(NewLength, 500, MaxArmDistance);

			UE_LOG(LogTemp, Warning, TEXT("ZoomValue: %f, NewLength: %f, TargetArmLength: %f"), ZoomValue, NewLength, CameraBoom->TargetArmLength);
		}
	}
	
}

float ABuildModePawn::MovementSpeedCalculation() const
{
	float MoveSensitivity = (CameraBoom->TargetArmLength)/100;
	MoveSensitivity = FMath::Clamp(MoveSensitivity, 5.0, 20.0);

	return MoveSensitivity;
}

