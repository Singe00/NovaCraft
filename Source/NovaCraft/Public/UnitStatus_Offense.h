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
		, fAttackSpeed(2.0f)
		, fGroundAttackEnabled(true)
		, fGroundWeaponName("Ground Attack")
		, fGroundAttackDamage(2.0f)
		, fGroundAttackRange(100.0f)
		, fGroundOffenseType(E_OffenseType::Normal)
		, fGroundAttackUpgradeIncreaseRate()
		, fGroundWeaponImage(nullptr)
		, fAirAttackEnabled(true)
		, fAirWeaponName("Air Attack")
		, fAirAttackDamage(4.0f)
		, fAirAttackRange(200.0f)
		, fAirOffenseType(E_OffenseType::Normal)
		, fAirAttackUpgradeIncreaseRate(2.0f)
		, fAirWeaponImage(nullptr)
	{};

public:
	// Can Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fUnitCanAttack;

	// Attack Speed (���� �ӵ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAttackSpeed;

	// Ground Status (���� ���� �ɷ�ġ)

	// Can Ground Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fGroundAttackEnabled;

	// Ground Weapon Name (���� ���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fGroundWeaponName;

	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackDamage;

	// Ground Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fGroundOffenseType;

	// Upgrade Increase Rate (���� ���� ���׷��̵� �� ������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fGroundAttackUpgradeIncreaseRate;

	// Ground Weapon Image (���� ���� ���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fGroundWeaponImage;

	// Air Status (���� ���� �ɷ�ġ)

	// Can Air Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fAirAttackEnabled;

	// Ground Weapon Name (���� ���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fAirWeaponName;


	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackDamage;

	// Air Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fAirOffenseType;

	// Upgrade Increase Rate (���� ���� ���׷��̵� �� ������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAirAttackUpgradeIncreaseRate;

	// Air Weapon Image (���� ���� ���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fAirWeaponImage;
};