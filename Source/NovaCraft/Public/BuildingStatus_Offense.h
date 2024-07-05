#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "BuildingStatus_Offense.generated.h"

USTRUCT(BlueprintType)
struct FBuildingStatus_Offense :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

public:

	FBuildingStatus_Offense()
		: fBuildingCanAttack(true)
		, fBuildingAttackSpeed(2.0f)
		, fBuildingGroundAttackEnabled(true)
		, fBuildingGroundWeaponName("Ground Attack")
		, fBuildingGroundAttackDamage(2.0f)
		, fBuildingGroundAttackRange(100.0f)
		, fGroundOffenseType(E_OffenseType::Normal)
		, fGroundWeaponImage(nullptr)
		, fBuildingAirAttackEnabled(true)
		, fBuildingAirWeaponName("Air Attack")
		, fBuildingAirAttackDamage(4.0f)
		, fBuildingAirAttackRange(200.0f)
		, fAirOffenseType(E_OffenseType::Normal)
		, fAirWeaponImage(nullptr)
	{};

public:
	// Can Attack (공격 가능 여부)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingCanAttack;

	// Attack Speed (공격 속도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAttackSpeed;

	// Ground Status (지상 공격 능력치)

	// Can Ground Attack (지상 공격 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingGroundAttackEnabled;

	// Ground Weapon Name (지상 무기 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingGroundWeaponName;

	// Attack Damage Ground (지상 대상 공격력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingGroundAttackDamage;

	// Ground Attack Range (지상 공격 사거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingGroundAttackRange;

	// Ground Attack Type (지상 공격 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fGroundOffenseType;

	// Ground Weapon Image (지상 공격 무기 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fGroundWeaponImage;

	// Air Status (공중 공격 능력치)

	// Can Air Attack (공중 공격 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingAirAttackEnabled;

	// Ground Weapon Name (공중 무기 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingAirWeaponName;


	// Attack Damage Ground (공중 대상 공격력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAirAttackDamage;

	// Air Attack Range (공중 공격 사거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAirAttackRange;

	// Ground Attack Type (공중 공격 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fAirOffenseType;

	// Air Weapon Image (공중 공격 무기 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fAirWeaponImage;
};