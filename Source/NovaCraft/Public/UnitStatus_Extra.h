#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "UnitStatus_Extra.generated.h"

USTRUCT(BlueprintType)
struct FUnitStatus_Extra :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FUnitStatus_Extra()
		: fRaceType(E_RaceType::RaceA)
		, fUnitName("Test Unit")
		, fKilledEnemyCount(0)
		, fUnit2DImage(nullptr)
		, fUnitPriority(1)
	{};

public:
	// Unit Rate (���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Unit Name (���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fUnitName;

	// Unit Killed Count (���� óġ ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fKilledEnemyCount;

	// Unit Image (���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fUnit2DImage;

	// Unit Priority (���� �켱����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fUnitPriority;
};