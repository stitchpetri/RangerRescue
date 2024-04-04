// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerGameState.h"

#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetMathLibrary.h"


ARangerGameState::ARangerGameState()
{
	GameTime.Init(0,3);
	GameDate.Init(0,3);

	Clockwork = 1.0f;
}

void ARangerGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FDivisionResult Result = SetClockwork(DeltaTime);
	Clockwork = Result.Remainder;
	DayTick = Result.ReturnValue;

	Clock();
	Calendar();
}



FDivisionResult ARangerGameState::SetClockwork(float DeltaSeconds) 
{
	

	const float value = (DeltaSeconds / TimeUnit) + Clockwork;
	FDivisionResult result = DivideWithRemainder(value, 24);
	

	return result;

}

void ARangerGameState::Clock()
{
	const float Dividend = Clockwork*3600;
	const FDivisionResult result = DivideWithRemainder(Dividend, 60.0f);
	Seconds = FMath::Floor(result.Remainder);

	const FDivisionResult Min = DivideWithRemainder(result.ReturnValue, 60);
	Minutes = FMath::Floor(Min.Remainder);

	const FDivisionResult Hour = DivideWithRemainder(Min.ReturnValue, 24);
	Hours = FMath::Floor(Hour.Remainder);

	
	GameTime[0] = Seconds;
	GameTime[1] = Minutes;
	GameTime[2] = Hours;
	
}

void ARangerGameState::Calendar()
{
	Day = Day+DayTick;
	const int DaysMonth = UKismetMathLibrary::DaysInMonth(Year, Month);

	if (Day > DaysMonth)
	{
		Day = 1;
		Month = Month+1;
	}
	if (Month > 12)
	{
		Month = 1;
		Year = Year+1;
	}

	GameDate[0] = Day;
	GameDate[1] = Month;
	GameDate[2] = Year;
}
