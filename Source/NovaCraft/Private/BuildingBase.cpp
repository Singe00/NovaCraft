// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Components/DecalComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	BuildingBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingBaseMesh"));
	BuildingBaseMesh->SetupAttachment(RootComponent);


	SelectedDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectedDecal"));
	SelectedDecal->SetupAttachment(BuildingBaseMesh);
	SelectedDecal->SetVisibility(false);
	SelectedDecal->SetRelativeRotation(FRotator(90, 0, 0));
	SelectedDecal->SetRelativeScale3D(FVector(0.25));
}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBase::InitStatus(FBuildingStatus_Defense NewDefenseStatus, FBuildingStatus_Offense NewOffenseStatus, FBuildingStatus_Utility NewUtilityStatus, FBuildingStatus_Extra NewExtraStatus, FBuildingStatus_Spawn NewSpawnStatus)
{
	SetDefenseStatus(NewDefenseStatus);
	SetOffenseStatus(NewOffenseStatus);
	SetUtilityStatus(NewUtilityStatus);
	SetExtraStatus(NewExtraStatus);
	SetSpawnStatus(NewSpawnStatus);
}

void ABuildingBase::SetDefenseStatus(FBuildingStatus_Defense NewDefenseStatus)
{
	this->BuildingStatus_Defense = NewDefenseStatus;
}

void ABuildingBase::SetOffenseStatus(FBuildingStatus_Offense NewOffenseStatus)
{
	this->BuildingStatus_Offense = NewOffenseStatus;
}

void ABuildingBase::SetUtilityStatus(FBuildingStatus_Utility NewUtilityStatus)
{
	this->BuildingStatus_Utility = NewUtilityStatus;
}

void ABuildingBase::SetExtraStatus(FBuildingStatus_Extra NewExtraStatus)
{
	this->BuildingStatus_Extra = NewExtraStatus;
}

void ABuildingBase::SetSpawnStatus(FBuildingStatus_Spawn NewSpawnStatus)
{
	this->BuildingStatus_Spawn = NewSpawnStatus;
}

void ABuildingBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuildingBase, TeamNumber);
	DOREPLIFETIME(ABuildingBase, TeamColor);
}
