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
	// Max Heealth (�ִ� ü��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingMaxHealth;

	// Now Health (���� ü��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingCurrentHealth;

	// Defense Shield Name (�� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingDefenseShieldName;

	// Defense (����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingDefense;

	// Defense Type (��� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DefenseType fDefenseType;

	// Defense Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fDefenseImage;
};