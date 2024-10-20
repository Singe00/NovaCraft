#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildingStatus_Spawn.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStatus_Spawn :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FBuildingStatus_Spawn()
		: fBuildingSpawnTime(5.0f)
		, fBuildingRequireSpawnGold(50)
		, fBuildingRequireSpawnGas(50)
		, fBuildingSpawnGridRow(2)
		, fBuildingSpawnGridCol(2)
		, fBuildingSpawnTechLevel(0)
	{};

public:
	// Spawn Time (생산 시간)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingSpawnTime;

	// Spawn Resource 1 (생산 시 요구 자원1 - 골드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingRequireSpawnGold;

	// Spawn Resource 2 (생산 시 요구 자원2 - 가스)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingRequireSpawnGas;

	// Spawn Grid Row(생산 Grid 행값)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnGridRow;

	// Spawn Grid Col(생산 Grid 행값)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnGridCol;

	// Spawn Resource 3 (생산 시 요구 자원4 - 테크)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnTechLevel;

};