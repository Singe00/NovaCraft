#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InputCoreTypes.h"
#include "ObjectActionPattern.generated.h"

USTRUCT(BlueprintType)
struct FObjectActionPattern :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FObjectActionPattern()
		: fPatternIndex(0)
		, fPatternName("Action")
		, fPatternImage(nullptr)
	{};

public:
	// Index (�ε���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fPatternIndex;

	// name (���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fPatternName;

	// Pattern Image (���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fPatternImage;

	// Pattern Image (�Է� Ű��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey fInputKeyValue;
};