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
	// Index (인덱스)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fPatternIndex;

	// name (패턴 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fPatternName;

	// Pattern Image (패턴 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fPatternImage;

	// Pattern Image (입력 키값)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey fInputKeyValue;
};