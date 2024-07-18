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
		, fBuildingPriority(1)
		, fBuildingType(E_BuildingType::None)
	{};

public:
	// Building Rate (유닛 종족)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Building Name (유닛 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingName;

	// Building Killed Count (유닛 처치 수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingKilledEnemyCount;

	// Building Image (유닛 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fBuilding2DImage;

	// Unit Priority (건물 우선순위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingPriority;

	// Building Type (건물 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_BuildingType fBuildingType;
};