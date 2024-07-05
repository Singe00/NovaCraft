#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "BuildingStatus_Utility.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStatus_Utility :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FBuildingStatus_Utility()
		: fBuildingMoveSpeed(300.0f)
		, fBuildingSightRange(50.0f)
	{};

public:
	// Move Speed (이동 속도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingMoveSpeed;

	// Sight (시야 범위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingSightRange;
};