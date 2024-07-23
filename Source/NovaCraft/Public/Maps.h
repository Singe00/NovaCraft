#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Maps.generated.h"

USTRUCT(BlueprintType)
struct FMaps :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FMaps()
		: fMapRefName("LV_MapRefName")
		, fMapName("MapDesignName")
		, fMaxMember(4)
		, fMapImage(nullptr)
	{};

public:
	// Map Ref Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fMapRefName;

	// Map Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fMapName;

	// Max Member
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fMaxMember;

	// Map Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fMapImage;

};