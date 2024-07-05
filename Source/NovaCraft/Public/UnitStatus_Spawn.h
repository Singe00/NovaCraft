#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitStatus_Spawn.generated.h"

USTRUCT(BlueprintType)
struct FUnitStatus_Spawn :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FUnitStatus_Spawn()
		: fSpawnTime(5.0f)
		, fRequireSpawnGold(50.0f)
		, fRequireSpawnGas(50.0f)
		, fRequirePopulation(1)
	{};

public:
	// Spawn Time (���� �ð�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fSpawnTime;

	// Spawn Resource 1 (���� �� �䱸 �ڿ�1 - ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fRequireSpawnGold;

	// Spawn Resource 2 (���� �� �䱸 �ڿ�2 - ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fRequireSpawnGas;

	// Spawn Resource 3 (���� �� �䱸 �ڿ�3 - �α�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fRequirePopulation;
};