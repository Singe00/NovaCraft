// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

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

void AUnitBase::GetSingleUnitSelectedInformation(
	FUnitStatus_Defense& OutUnitStatus_Defense,
	FUnitStatus_Offense& OutUnitStatus_Offense,
	FUnitStatus_Utility& OutUnitStatus_Utility,
	FUnitStatus_Extra& OutUnitStatus_Extra) const
{
	OutUnitStatus_Defense = UnitStatus_Defense;
	OutUnitStatus_Offense = UnitStatus_Offense;
	OutUnitStatus_Utility = UnitStatus_Utility;
	OutUnitStatus_Extra = UnitStatus_Extra;
}

void AUnitBase::GetGroundAttackStatus(float& OutDamage, int& OutAttackTimes, E_OffenseType& OutOffenseType) const
{
	OutDamage = UnitStatus_Offense.fGroundAttackDamage;
	OutAttackTimes = UnitStatus_Offense.fGroundAttackTimes;
	OutOffenseType = UnitStatus_Offense.fGroundOffenseType;
}

void AUnitBase::GetAirAttackStatus(float& OutDamage, int& OutAttackTimes, E_OffenseType& OutOffenseType) const
{
	OutDamage = UnitStatus_Offense.fAirAttackDamage;
	OutAttackTimes = UnitStatus_Offense.fAirAttackTimes;
	OutOffenseType = UnitStatus_Offense.fAirOffenseType;
}


void AUnitBase::InitStatus(FUnitStatus_Defense NewDefenseStatus, FUnitStatus_Offense NewOffenseStatus, FUnitStatus_Utility NewUtilityStatus, FUnitStatus_Extra NewExtraStatus, FUnitStatus_Spawn NewSpawnStatus, TArray<FObjectActionPattern> NewObjectActionPattern)
{
	SetDefenseStatus(NewDefenseStatus);
	SetOffenseStatus(NewOffenseStatus);
	SetUtilityStatus(NewUtilityStatus);
	SetExtraStatus(NewExtraStatus);
	SetSpawnStatus(NewSpawnStatus);
	SetUnitActionPatterns(NewObjectActionPattern);
}

void AUnitBase::SetDefenseStatus(FUnitStatus_Defense NewDefenseStatus)
{
	this->UnitStatus_Defense = NewDefenseStatus;
}

void AUnitBase::SetOffenseStatus(FUnitStatus_Offense NewOffenseStatus)
{
	this->UnitStatus_Offense = NewOffenseStatus;
}

void AUnitBase::SetUtilityStatus(FUnitStatus_Utility NewUtilityStatus)
{
	this->UnitStatus_Utility = NewUtilityStatus;
}

void AUnitBase::SetExtraStatus(FUnitStatus_Extra NewExtraStatus)
{
	this->UnitStatus_Extra = NewExtraStatus;
}

void AUnitBase::SetSpawnStatus(FUnitStatus_Spawn NewSpawnStatus)
{
	this->UnitStatus_Spawn = NewSpawnStatus;
}

void AUnitBase::SetUnitActionPatterns(TArray<FObjectActionPattern> NewObjectActionPattern)
{
	this->ActionPattern = NewObjectActionPattern;
}

void AUnitBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUnitBase, TeamNumber);
	DOREPLIFETIME(AUnitBase, TeamColor);
}

float AUnitBase::CalculateDamage(float Damage, int AttackTimes, E_OffenseType OffenseType)
{
	float damageMultiplier = DamageMatrix[static_cast<int>(OffenseType)][static_cast<int>(UnitStatus_Defense.fDefenseType)];
	float finalDamage = ((((Damage/ AttackTimes) * damageMultiplier) - UnitStatus_Defense.fDefense) * AttackTimes);

	if (finalDamage < 0.5)
	{
		finalDamage = 0.5;
	}

	return finalDamage;
}

bool AUnitBase::CustomTakeDamage(float Damage)
{
	UnitStatus_Defense.fCurrentHealth -= Damage;

	HpBarUpdate.Broadcast(UnitStatus_Defense.fCurrentHealth, UnitStatus_Defense.fMaxHealth);

	if (UnitStatus_Defense.fCurrentHealth <= 0)
	{
		this->isDead = true;

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		OnUnitDead.Broadcast(this);


		return false;
	}
	else
	{
		OnUnitDamaged.Broadcast(this);
	}

	return true;
}



