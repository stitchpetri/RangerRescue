// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "SavingSystem/SaveInterface.h"
#include "MainCharacter.generated.h"

// FORWARD DECLARES -----------------------

class ABuildModePawn;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
//- ---------------------------------------
UCLASS()
class RANGERRESCUE_API AMainCharacter : public ACharacter, public ISaveInterface
{
	GENERATED_BODY()

private:

	// -------------------------- INPUT VARIABLES--------------------------------------
	// --------------------------------------------------------------------------------
	/** Camera boom positioning the camera behind the character */
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Interaction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* FocusAction;

	// -------------------------------------------------------------------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deafult", meta = (AllowPrivateAccess = "true"))
	float ViewPitchMin = -50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deafult", meta = (AllowPrivateAccess = "true"))
	float ViewPitchMax = 10.0f;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default|BuildMode", meta = (AllowPrivateAccess = "true"))
	ABuildModePawn* BuildModePawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default|Focus", meta = (AllowPrivateAccess = "true"))
	float NormalSpringArmLength = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default|Focus", meta = (AllowPrivateAccess = "true"))
	float FocusSpringArmLength = 150.0f;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	//UInventoryComponent* Inventory = nullptr;



public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Implement functions from ISaveInterface (but leave them as pure virtual)
	virtual void OnBeforeSave_Implementation() override;
	virtual FString GetUniqueSaveName_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ----------INPUT FUNCTIONS -----------------------

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Focus(const FInputActionValue& Value);
	void EndFocus(const FInputActionValue& Value);
	UFUNCTION()
	void TimelineProgress(float Value);

	UFUNCTION(BlueprintCallable)
	void OpenBuildMode();

	UFUNCTION(BlueprintCallable)
	void CloseBuildMode();

	UPROPERTY(VisibleAnywhere)
	bool bInBuildMode = false;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	

	FTimeline FocusTimeline;
	
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloatAsset;

	class UAIPerceptionStimuliSourceComponent* StimuliSource;

	void SetupStimulusSource();
	

};
