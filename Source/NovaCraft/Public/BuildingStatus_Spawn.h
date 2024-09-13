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
	// Spawn Time (���� �ð�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingSpawnTime;

	// Spawn Resource 1 (���� �� �䱸 �ڿ�1 - ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingRequireSpawnGold;

	// Spawn Resource 2 (���� �� �䱸 �ڿ�2 - ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingRequireSpawnGas;

	// Spawn Grid Row(���� Grid �ప)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnGridRow;

	// Spawn Grid Col(���� Grid �ప)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnGridCol;

	// Spawn Resource 3 (���� �� �䱸 �ڿ�4 - ��ũ)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fBuildingSpawnTechLevel;

};