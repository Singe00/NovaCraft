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
	// Building Rate (���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Building Name (���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingName;

	// Building Killed Count (���� óġ ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingKilledEnemyCount;

	// Building Image (���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fBuilding2DImage;

	// Unit Priority (�ǹ� �켱����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingPriority;

	// Building Type (�ǹ� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_BuildingType fBuildingType;
};