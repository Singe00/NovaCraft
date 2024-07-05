#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "BuildingStatus_Defense.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStatus_Defense :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FBuildingStatus_Defense()
		: fBuildingMaxHealth(10.0f)
		, fBuildingCurrentHealth(10.0f)
		, fBuildingDefenseShieldName("Sheild")
		, fBuildingDefense(1.0f)
		, fDefenseType(E_DefenseType::Building)
		, fDefenseImage(nullptr)
	{};

public:
	// Max Heealth (최대 체력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingMaxHealth;

	// Now Health (현재 체력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingCurrentHealth;

	// Defense Shield Name (방어구 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingDefenseShieldName;

	// Defense (방어력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingDefense;

	// Defense Type (방어 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DefenseType fDefenseType;

	// Defense Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fDefenseImage;
};