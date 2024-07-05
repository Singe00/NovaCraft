#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "BuildingStatus_Utility.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStatus_Utility :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FBuildingStatus_Utility()
		: fBuildingMoveSpeed(300.0f)
		, fBuildingSightRange(50.0f)
	{};

public:
	// Move Speed (�̵� �ӵ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingMoveSpeed;

	// Sight (�þ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingSightRange;
};