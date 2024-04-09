// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RangerGameState.generated.h"

USTRUCT(BlueprintType)
struct FDivisionResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ReturnValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Remainder;
};

/**
 * 
 */
UCLASS()
class RANGERRESCUE_API ARangerGameState : public AGameStateBase
{
	GENERATED_BODY()


public:
	ARangerGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
	FDivisionResult DivideWithRemainder(float Dividend, float Divisor);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	float TimeUnit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
	float Clockwork;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Hours;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
	TArray<int>  GameTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults|Time")
	int Year;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
	TArray<int> GameDate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time")
	int  DayTick;

	// Gets current clockwork returned in a struct
	UFUNCTION(BlueprintPure)
	FDivisionResult SetClockwork(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void Clock();

	UFUNCTION(BlueprintCallable)
	void Calendar();

	/*
	UFUNCTION(BlueprintImplementableEvent)
	void SetTimeUI(TArray<int32> Time);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetDayUI(TArray<int32> Date);
	*/
};
