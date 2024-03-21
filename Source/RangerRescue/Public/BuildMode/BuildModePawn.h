// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BuildModePawn.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UStaticMeshComponent;
UCLASS()
class RANGERRESCUE_API ABuildModePawn : public APawn
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

public:
	// Sets default values for this pawn's properties
	ABuildModePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PawnMesh;
	

	// ----------INPUT FUNCTIONS -----------------------

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Pan(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	float MovementSpeedCalculation() const;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* BuildModeCamera;



	//-------------------Movement Variables -------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool DisableCamNav = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float FastMoveMultiplier = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PanSensitivity = 5.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ZoomSensitivity = 50.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxArmDistance= 2000.0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
