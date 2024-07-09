#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "UnitStatus_Defense.generated.h"

USTRUCT(BlueprintType)
struct FUnitStatus_Defense :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FUnitStatus_Defense()
		: fMaxHealth(10.0f)
		, fCurrentHealth(10.0f)
		, fDefenseShieldName("Sheild")
		, fDefense(1.0f)
		, fDefenseType(E_DefenseType::Small)
		, fDefenseUpgradeIncreaseRate(1.0f)
		, fDefenseImage(nullptr)
		, fUnitType(E_UnitType::Ground)
	{};

public:
	// Max Heealth (�ִ� ü��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fMaxHealth;

	// Now Health (���� ü��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fCurrentHealth;

	// Defense Shield Name (���� �� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fDefenseShieldName;

	// Defense (����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDefense;

	// Defense Type (��� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DefenseType fDefenseType;

	// Upgrade Increase Rate (���׷��̵� �� ������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDefenseUpgradeIncreaseRate;

	// Defense Image (�� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fDefenseImage;

	// MoveType (�̵�
	E_UnitType fUnitType;
};