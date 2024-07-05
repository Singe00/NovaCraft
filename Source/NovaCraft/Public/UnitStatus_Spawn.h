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
	// Spawn Time (생산 시간)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fSpawnTime;

	// Spawn Resource 1 (생산 시 요구 자원1 - 골드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fRequireSpawnGold;

	// Spawn Resource 2 (생산 시 요구 자원2 - 가스)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fRequireSpawnGas;

	// Spawn Resource 3 (생산 시 요구 자원3 - 인구)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fRequirePopulation;
};