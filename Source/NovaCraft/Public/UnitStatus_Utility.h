#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UnitStatus_Utility.generated.h"

USTRUCT(BlueprintType)
struct FUnitStatus_Utility :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FUnitStatus_Utility()
		: fMoveSpeed(300.0f)
		, fSightRange(5.0f)
	{};

public:
	// Move Speed (�̵� �ӵ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fMoveSpeed;

	// Sight (�þ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fSightRange;
};