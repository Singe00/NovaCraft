// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/DecalComponent.h"
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

void AUnitBase::InitStatus(FUnitStatus_Defense NewDefenseStatus, FUnitStatus_Offense NewOffenseStatus, FUnitStatus_Utility NewUtilityStatus, FUnitStatus_Extra NewExtraStatus, FUnitStatus_Spawn NewSpawnStatus)
{
	SetDefenseStatus(NewDefenseStatus);
	SetOffenseStatus(NewOffenseStatus);
	SetUtilityStatus(NewUtilityStatus);
	SetExtraStatus(NewExtraStatus);
	SetSpawnStatus(NewSpawnStatus);
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

void AUnitBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUnitBase, TeamNumber);
	DOREPLIFETIME(AUnitBase, TeamColor);
}



