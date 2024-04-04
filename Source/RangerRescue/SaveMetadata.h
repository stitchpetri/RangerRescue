#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "SaveMetadata.generated.h"

USTRUCT(BlueprintType)
struct FSaveMetadata
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	FString SlotName;
	
	// date that the game was saved
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	FDateTime Date;
	
};
