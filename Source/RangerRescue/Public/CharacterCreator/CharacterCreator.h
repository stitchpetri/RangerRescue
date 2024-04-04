// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/Image.h"
#include "GameFramework/Actor.h"

#include "CharacterCreator.generated.h"

class ACustomCharacter;
class UCameraComponent;
class USpringArmComponent;
class UImage;

UCLASS()
class RANGERRESCUE_API ACharacterCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterCreator();

	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

	// -------------------------Scene-------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* CharacterSpawnLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	//--------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	ACustomCharacter* Character;

	// ------------------- INPUT ----------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	bool isRotatingCamera = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement")
	float MouseSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement")
	float ZoomSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement")
	float MinZoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Movement")
	float MaxZoom;
	
	UFUNCTION(BlueprintCallable)
	void Zoom(float Amount);

	void CameraRotationUpdate(float DeltaTime) const;

	void InteractUpdate(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void StartInteract();

	UFUNCTION(BlueprintCallable)
	void StopInteract();


	
	//=============================================================================
	// ---------------------------Manipulation-----------------------------------
	
	//void Manipulate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manipulation")
	FString CurrentManipulation;

	bool isManipulating;

	UFUNCTION(BlueprintImplementableEvent)
	void ManipulateUpdate(float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Manipulation")
	USkeletalMesh* FaceMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Manipulation")
	UMaterialInstance* FaceMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulation")
	float ManipulateSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manipulation")
	bool isManipulatingDepth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manipulation")
	bool isManipulatingDepthFromRight;

	// Checks if player is manipulating the depth or width morph depending on camera angle
	void CheckforDepth();

	void HighlightUpdate();

	UFUNCTION(BlueprintImplementableEvent)
	void SetHighlightParams(FName ParameterName, float Value);

	//=============================================================================
	// ---------------------------Skin Tint-----------------------------------

	UFUNCTION(BlueprintCallable)
	void SkinTintUpdate(UImage* Picker, float DeltaSeconds);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Skin")
	float SkinTintSpeed= 100.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skin")
	FVector2D SkinTintCoordinates = FVector2d(64.0, 64.0);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skin")
	bool isSettingSkinTint = false;

	UFUNCTION(BlueprintImplementableEvent)
	void SetVectorParam(FName ParameterName, FVector2D Value);


	//=============================================================================
	// ---------------------------Hair -----------------------------------

	UFUNCTION(BlueprintCallable)
	void HairTintUpdate(UImage* Picker, float DeltaSeconds);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skin")
	bool isSettingHairTint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skin")
	FVector2D HairTintCoordinates = FVector2d(64.0, 64.0);
	
};
