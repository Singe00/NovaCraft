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
		, fRequireSpawnGold(50)
		, fRequireSpawnGas(50)
		, fRequirePopulation(1)
		, fSpawnTechLevel(0)
	{};

public:
	// Spawn Time (���� �ð�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fSpawnTime;

	// Spawn Resource 1 (���� �� �䱸 �ڿ�1 - ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fRequireSpawnGold;

	// Spawn Resource 2 (���� �� �䱸 �ڿ�2 - ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fRequireSpawnGas;

	// Spawn Resource 3 (���� �� �䱸 �ڿ�3 - �α�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fRequirePopulation;

	// Spawn Resource 3 (���� �� �䱸 �ڿ�4 - ��ũ)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fSpawnTechLevel;
};