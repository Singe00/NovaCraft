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
	// Max Heealth (최대 체력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fMaxHealth;

	// Now Health (현재 체력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fCurrentHealth;

	// Defense Shield Name (지상 방어구 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fDefenseShieldName;

	// Defense (방어력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDefense;

	// Defense Type (방어 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_DefenseType fDefenseType;

	// Upgrade Increase Rate (업그레이드 시 증가량)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDefenseUpgradeIncreaseRate;

	// Defense Image (방어구 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fDefenseImage;

	// MoveType (이동
	E_UnitType fUnitType;
};