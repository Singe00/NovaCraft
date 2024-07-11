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
	// Unit Rate (À¯´Ö Á¾Á·)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_RaceType fRaceType;

	// Unit Name (À¯´Ö ÀÌ¸§)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fUnitName;

	// Unit Killed Count (À¯´Ö Ã³Ä¡ ¼ö)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fKilledEnemyCount;

	// Unit Image (À¯´Ö ÀÌ¹ÌÁö)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fUnit2DImage;

	// Unit Priority (À¯´Ö ¿ì¼±¼øÀ§)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fUnitPriority;
};