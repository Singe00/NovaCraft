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

	// Max Heealth (�ִ� ü��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float MaxHealth;

	// Now Health (���� ü��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float CurrentHealth;

	// Defense Shield Name (���� �� �̸�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	FString DefenseShieldName;

	// Defense (����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float Defense;

	// Defense Type (��� Ÿ��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	E_DefenseType DefenseType;

	// Upgrade Increase Rate (���׷��̵� �� ������)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Defense Status")
	float DefenseUpgradeIncreaseRate;

	// Offense Status
protected:

	// Can Attack (���� ���� ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status")
	bool UnitCanAttack;

	// Attack Speed (���� �ӵ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status", meta = (EditCondition = "UnitCanAttack"))
	float AttackSpeed;

	// Ground Status (���� ���� �ɷ�ġ)

	// Ground Weapon Name (���� ���� �̸�)

	// Can Ground Attack (���� ���� ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "UnitCanAttack"))
	bool GroundAttackEnabled;

	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	FString GroundWeaponName;

	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackDamage;

	// Ground Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	E_OffenseType GroundOffenseType;

	// Upgrade Increase Rate (���� ���� ���׷��̵� �� ������)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Ground Attack", meta = (EditCondition = "GroundAttackEnabled"))
	float GroundAttackUpgradeIncreaseRate;

	// Air Status (���� ���� �ɷ�ġ)

	// Can Air Attack (���� ���� ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "UnitCanAttack"))
	bool AirAttackEnabled;

	// Ground Weapon Name (���� ���� �̸�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	FString AirWeaponName;


	// Attack Damage Ground (���� ��� ���ݷ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackDamage;

	// Air Attack Range (���� ���� ��Ÿ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackRange;

	// Ground Attack Type (���� ���� Ÿ��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	E_OffenseType AirOffenseType;

	// Upgrade Increase Rate (���� ���� ���׷��̵� �� ������)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Offense Status|Air Attack", meta = (EditCondition = "AirAttackEnabled"))
	float AirAttackUpgradeIncreaseRate;

	//Utility Status
protected:

	// Move Speed (�̵� �ӵ�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Utility Status")
	float MoveSpeed;

	// Sight (�þ� ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Utility Status")
	float SightRange;

	// Extra Status
protected:

	// Unit Rate (���� ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	E_RaceType RaceType;

	// Unit Name (���� �̸�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	FString UnitName;

	// Unit Killed Count (���� óġ ��)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	int KilledEnemyCount;

	// Unit Image (���� �̹���)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Extra Status")
	UTexture2D* Unit2DImage;

	// Spawn Status
protected:

	// Spawn Time (���� �ð�)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float SpawnTime;

	// Spawn Resource 1 (���� �� �䱸 �ڿ�1 - ���)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float RequireSpawnGold;

	// Spawn Resource 2 (���� �� �䱸 �ڿ�2 - ����)
	UPROPERTY(VisibleAnywhere, Category = "Unit Status|Spawn Status")
	float RequireSpawnGas;

	// Spawn Resource 3 (���� �� �䱸 �ڿ�3 - �α�)
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
