// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitBase.generated.h"

UENUM(BlueprintType)
enum class E_RaceType : uint8
{
	None UMETA(DisplayName = "None"),
	RaceA UMETA(DisplayName = "RaceA"),
	RaceB UMETA(DisplayName = "RaceB"),
	RaceC UMETA(DisplayName = "RaceC"),
};

UENUM(BlueprintType)
enum class E_DefenseType : uint8
{
	None UMETA(DisplayName = "None"),
	Small UMETA(DisplayName = "Small"),
	Medium UMETA(DisplayName = "Medium"),
	Large UMETA(DisplayName = "Large"),
};

UENUM(BlueprintType)
enum class E_OffenseType : uint8
{
	None UMETA(DisplayName = "None"),
	Normal UMETA(DisplayName = "Normal"),
	Explosive UMETA(DisplayName = "Explosive"),
	Concussive UMETA(DisplayName = "Concussive"),
	Spell UMETA(DisplayName = "Spell"),
};

UCLASS()
class NOVACRAFT_API AUnitBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* SelectedDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* HighlightDecal;

	// All Common Status Under Here

	// Defence Status
protected:

	// Max Heealth (최대 체력)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float MaxHealth;

	// Now Health (현재 체력)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float CurrentHealth;

	// Defense Shield Name (지상 방어구 이름)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	FString DefenseShieldName;

	// Defense (방어력)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float Defense;

	// Defense Type (방어 타입)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	E_DefenseType DefenseType;

	// Upgrade Increase Rate (업그레이드 시 증가량)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float DefenseUpgradeIncreaseRate;

	// Offense Status
protected:

	// Can Attack (공격 가능 여부)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status")
	bool UnitCanAttack;

	// Attack Speed (공격 속도)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status", meta = (EditCondition = "UnitCanAttack"))
	float AttackSpeed;

	// Ground Status (지상 공격 능력치)

	// Ground Weapon Name (지상 무기 이름)

	// Can Ground Attack (지상 공격 가능)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "UnitCanAttack"))
	bool GroundAttackEnabled;

	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	FString GroundWeaponName;

	// Attack Damage Ground (지상 대상 공격력)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackDamage;

	// Ground Attack Range (지상 공격 사거리)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackRange;

	// Ground Attack Type (지상 공격 타입)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	E_OffenseType GroundOffenseType;

	// Upgrade Increase Rate (지상 공격 업그레이드 시 증가량)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackUpgradeIncreaseRate;

	// Air Status (공중 공격 능력치)

	// Can Air Attack (공중 공격 가능)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "UnitCanAttack"))
	bool AirAttackEnabled;

	// Ground Weapon Name (공중 무기 이름)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	FString AirWeaponName;


	// Attack Damage Ground (공중 대상 공격력)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackDamage;

	// Air Attack Range (공중 공격 사거리)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackRange;

	// Ground Attack Type (공중 공격 타입)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	E_OffenseType AirOffenseType;

	// Upgrade Increase Rate (공중 공격 업그레이드 시 증가량)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackUpgradeIncreaseRate;

	//Utility Status
protected:

	// Move Speed (이동 속도)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Utility Status")
	float MoveSpeed;

	// Sight (시야 범위)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Utility Status")
	float SightRange;

	// Extra Status
protected:

	// Unit Rate (유닛 종족)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	E_RaceType RaceType;

	// Unit Name (유닛 이름)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	FString UnitName;

	// Unit Killed Count (유닛 처치 수)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	int KilledEnemyCount;

	// Unit Image (유닛 이미지)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	UTexture2D* Unit2DImage;

	// Spawn Status
protected:

	// Spawn Time (생산 시간)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float SpawnTime;

	// Spawn Resource 1 (생산 시 요구 자원1 - 골드)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float RequireSpawnGold;

	// Spawn Resource 2 (생산 시 요구 자원2 - 가스)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float RequireSpawnGas;

	// Spawn Resource 3 (생산 시 요구 자원3 - 인구)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	int RequirePopulation;


	// Setter
public:
	void InitStatus();

	UFUNCTION(BlueprintCallable)
	void SetDefenseStatus(float NewMaxHealth, float NewCurrentHealth, FString NewDefenseShieldName, float NewDefense, E_DefenseType NewDefenseType, float NewDefenseUpgradeIncreaseRate);

	UFUNCTION(BlueprintCallable)
	void SetOffenseStatus(bool NewUnitCanAttack, float NewAttackSpeed,
		bool NewGroundAttackEnabled, FString NewGroundWeaponName, float NewGroundAttackDamage, float NewGroundAttackRange, E_OffenseType NewGroundOffenseType, float NewGroundAttackUpgradeIncreaseRate,
		bool NewAirAttackEnabled, FString NewAirWeaponName, float NewAirAttackDamage, float NewAirAttackRange, E_OffenseType NewAirOffenseType, float NewAirAttackUpgradeIncreaseRate);

	UFUNCTION(BlueprintCallable)
	void SetUtilityStatus(float NewMoveSpeed, float NewSightRange);

	UFUNCTION(BlueprintCallable)
	void SetExtraStatus(E_RaceType NewRaceType, FString NewUnitName, int NewKilledEnemyCount, UTexture2D* NewUnit2DImage);

	UFUNCTION(BlueprintCallable)
	void SetSpawnStatus(float NewSpawnTime, float NewRequireSpawnGold, float NewRequireSpawnGas, int NewRequirePopulation);

	// Function
public:


};
