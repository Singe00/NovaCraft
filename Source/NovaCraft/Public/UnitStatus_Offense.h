#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorEnums.h"
#include "UnitStatus_Offense.generated.h"

USTRUCT(BlueprintType)
struct FUnitStatus_Offense :public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FUnitStatus_Offense()
		: fUnitCanAttack(true)
		, fGroundAttackEnabled(true)
		, fGroundWeaponName("Ground Attack")
		, fGroundAttackDamage(2.0f)
		, fGroundAttackSpeed(1.0f)
		, fGroundAttackTimes(1)
		, fGroundAttackRange(100.0f)
		, fGroundOffenseType(E_OffenseType::Normal)
		, fGroundAttackUpgradeIncreaseRate()
		, fGroundWeaponImage(nullptr)
		, fAirAttackEnabled(true)
		, fAirWeaponName("Air Attack")
		, fAirAttackDamage(4.0f)
		, fAirAttackSpeed(1.0f)
		, fAirAttackTimes(1)
		, fAirAttackRange(200.0f)
		, fAirOffenseType(E_OffenseType::Normal)
		, fAirAttackUpgradeIncreaseRate(2.0f)
		, fAirWeaponImage(nullptr)
	{};

public:
	// Can Attack (공격 가능 여부)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fUnitCanAttack;

	// Ground Status (지상 공격 능력치)

	// Can Ground Attack (지상 공격 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fGroundAttackEnabled;

	// Ground Weapon Name (지상 무기 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fGroundWeaponName;

	// Attack Damage Ground (지상 대상 공격력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackDamage;

	// Attack Speed (지상 공격 속도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackSpeed;

	// Attack Speed (지상 공격 횟수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fGroundAttackTimes;

	// Ground Attack Range (지상 공격 사거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackRange;

	// Ground Attack Type (지상 공격 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fGroundOffenseType;

	// Upgrade Increase Rate (지상 공격 업그레이드 시 증가량)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackUpgradeIncreaseRate;

	// Ground Weapon Image (지상 공격 무기 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fGroundWeaponImage;

	// Air Status (공중 공격 능력치)

	// Can Air Attack (공중 공격 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fAirAttackEnabled;

	// Ground Weapon Name (공중 무기 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fAirWeaponName;


	// Attack Damage Ground (공중 대상 공격력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackDamage;

	// Attack Speed (공중 공격 속도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackSpeed;

	// Attack Speed (공중 공격 횟수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int fAirAttackTimes;

	// Air Attack Range (공중 공격 사거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackRange;

	// Ground Attack Type (공중 공격 타입)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fAirOffenseType;

	// Upgrade Increase Rate (공중 공격 업그레이드 시 증가량)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackUpgradeIncreaseRate;

	// Air Weapon Image (공중 공격 무기 이미지)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fAirWeaponImage;
};