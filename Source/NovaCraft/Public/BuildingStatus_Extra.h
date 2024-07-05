#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "BuildingStatus_Extra.generated.h"


USTRUCT(BlueprintType)
struct FBuildingStatus_Extra :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FBuildingStatus_Extra()
		: fRaceType(E_RaceType::RaceA)
		, fBuildingName("Test Building")
		, fBuildingKilledEnemyCount(0)
		, fBuilding2DImage(nullptr)
	{};

public:
	// Building Rate (À¯´Ö Á¾Á·)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Building Name (À¯´Ö ÀÌ¸§)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingName;

	// Building Killed Count (À¯´Ö Ã³Ä¡ ¼ö)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingKilledEnemyCount;

	// Building Image (À¯´Ö ÀÌ¹ÌÁö)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fBuilding2DImage;
};