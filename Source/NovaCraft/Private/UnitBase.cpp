// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/DecalComponent.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SelectedDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectedDecal"));
	SelectedDecal->SetupAttachment(GetMesh());
	SelectedDecal->SetVisibility(false);
	SelectedDecal->SetRelativeRotation(FRotator(90, 0, 0));
	SelectedDecal->SetRelativeScale3D(FVector(0.25));

	HighlightDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("HighlightDecal"));
	HighlightDecal->SetupAttachment(GetMesh());
	HighlightDecal->SetVisibility(false);
	HighlightDecal->SetRelativeRotation(FRotator(90, 0, 0));
	HighlightDecal->SetRelativeScale3D(FVector(0.25));

	InitStatus();
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnitBase::InitStatus()
{
	// Defense Status
	this->MaxHealth = 0;
	this->CurrentHealth = 0;
	this->DefenseShieldName = "";
	this->Defense = 0;
	this->DefenseType = E_DefenseType::None;
	this->DefenseUpgradeIncreaseRate = 0;

	// Offense Status
	this->UnitCanAttack = false;

	this->AttackSpeed = 0;

	this->GroundAttackEnabled = false;
	this->GroundWeaponName = "";
	this->GroundAttackDamage = 0;
	this->GroundAttackRange = 0;
	this->GroundOffenseType = E_OffenseType::None;
	this->GroundAttackUpgradeIncreaseRate = 0;

	this->AirAttackEnabled = false;
	this->AirWeaponName = "";
	this->AirAttackDamage = 0;
	this->AirAttackRange = 0;
	this->AirOffenseType = E_OffenseType::None;
	this->AirAttackUpgradeIncreaseRate = 0;

	// Utility Status
	this->MoveSpeed = 0;
	this->SightRange = 0;

	// ExtraStatus
	this->RaceType = E_RaceType::None;
	this->UnitName = "";
	this->KilledEnemyCount = 0;
	this->Unit2DImage = nullptr;

	// Spawn Status
	this->SpawnTime = 0;
	this->RequireSpawnGold = 0;
	this->RequireSpawnGas = 0;
	this->RequirePopulation = 0;
}

void AUnitBase::SetDefenseStatus(float NewMaxHealth, float NewCurrentHealth, FString NewDefenseShieldName, float NewDefense, E_DefenseType NewDefenseType, float NewDefenseUpgradeIncreaseRate)
{
	this->MaxHealth = NewMaxHealth;
	this->CurrentHealth = NewCurrentHealth;
	this->DefenseShieldName = NewDefenseShieldName;
	this->Defense = NewDefense;
	this->DefenseType = NewDefenseType;
	this->DefenseUpgradeIncreaseRate = NewDefenseUpgradeIncreaseRate;
}

void AUnitBase::SetOffenseStatus(bool NewUnitCanAttack, float NewAttackSpeed, bool NewGroundAttackEnabled, FString NewGroundWeaponName, float NewGroundAttackDamage, float NewGroundAttackRange, E_OffenseType NewGroundOffenseType, float NewGroundAttackUpgradeIncreaseRate, bool NewAirAttackEnabled, FString NewAirWeaponName, float NewAirAttackDamage, float NewAirAttackRange, E_OffenseType NewAirOffenseType, float NewAirAttackUpgradeIncreaseRate)
{
	this->UnitCanAttack = NewUnitCanAttack;

	if (UnitCanAttack)
	{
		this->AttackSpeed = NewAttackSpeed;

		this->GroundAttackEnabled = NewGroundAttackEnabled;
		if (GroundAttackEnabled)
		{
			this->GroundWeaponName = NewGroundWeaponName;
			this->GroundAttackDamage = NewGroundAttackDamage;
			this->GroundAttackRange = NewGroundAttackRange;
			this->GroundOffenseType = NewGroundOffenseType;
			this->GroundAttackUpgradeIncreaseRate = NewGroundAttackUpgradeIncreaseRate;
		}

		this->AirAttackEnabled = NewAirAttackEnabled;
		if (AirAttackEnabled)
		{
			this->AirWeaponName = NewAirWeaponName;
			this->AirAttackDamage = NewAirAttackDamage;
			this->AirAttackRange = NewAirAttackRange;
			this->AirOffenseType = NewAirOffenseType;
			this->AirAttackUpgradeIncreaseRate = NewAirAttackUpgradeIncreaseRate;
		}
	}


}

void AUnitBase::SetUtilityStatus(float NewMoveSpeed, float NewSightRange)
{
	this->MoveSpeed = NewMoveSpeed;
	this->SightRange = NewSightRange;
}

void AUnitBase::SetExtraStatus(E_RaceType NewRaceType, FString NewUnitName, int NewKilledEnemyCount, UTexture2D* NewUnit2DImage)
{
	this->RaceType = NewRaceType;
	this->UnitName = NewUnitName;
	this->KilledEnemyCount = NewKilledEnemyCount;
	this->Unit2DImage = NewUnit2DImage;
}

void AUnitBase::SetSpawnStatus(float NewSpawnTime, float NewRequireSpawnGold, float NewRequireSpawnGas, int NewRequirePopulation)
{
	this->SpawnTime = NewSpawnTime;
	this->RequireSpawnGold = NewRequireSpawnGold;
	this->RequireSpawnGas = NewRequireSpawnGas;
	this->RequirePopulation = NewRequirePopulation;
}

