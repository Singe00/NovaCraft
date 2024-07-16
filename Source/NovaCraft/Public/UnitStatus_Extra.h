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
	// Unit Rate (유닛 종족)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Unit Name (유닛 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fUnitName;

	// Unit Killed Count (유닛 처치 수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fKilledEnemyCount;

	// Unit Image (유닛 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fUnit2DImage;

	// Unit Priority (유닛 우선순위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fUnitPriority;

	// Building Type (건물 타입)

};