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
	// Can Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingCanAttack;

	// Attack Speed (���� �ӵ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAttackSpeed;

	// Ground Status (���� ���� �ɷ�ġ)

	// Can Ground Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingGroundAttackEnabled;

	// Ground Weapon Name (���� ���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingGroundWeaponName;

	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingGroundAttackDamage;

	// Ground Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingGroundAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fGroundOffenseType;

	// Ground Weapon Image (���� ���� ���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fGroundWeaponImage;

	// Air Status (���� ���� �ɷ�ġ)

	// Can Air Attack (���� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool fBuildingAirAttackEnabled;

	// Ground Weapon Name (���� ���� �̸�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString fBuildingAirWeaponName;


	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAirAttackDamage;

	// Air Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fBuildingAirAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_OffenseType fAirOffenseType;

	// Air Weapon Image (���� ���� ���� �̹���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* fAirWeaponImage;
};