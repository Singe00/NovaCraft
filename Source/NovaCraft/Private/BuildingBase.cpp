// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Components/DecalComponent.h"
#include "UnitBase.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/00_Work/Common/Widget/CommonObject/WB_HpBar'_C"));

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidget"));

	if (UW.Succeeded())
	{
		HpBarWidget->SetupAttachment(RootComponent);
		HpBarWidget->SetWidgetClass(UW.Class);
		HpBarWidget->SetDrawSize(FVector2D(100, 10));
		HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}

	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollision"));
	OverlapCollision->SetupAttachment(BuildingBaseMesh);
	OverlapCollision->GetBodyInstance()->SetSmoothEdgeCollisionsEnabled(true);
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

void ABuildingBase::GetBuildSpawnGridValue(int& RowValue, int& ColValue) const
{
	RowValue = BuildingStatus_Spawn.fBuildingSpawnGridRow;
	ColValue = BuildingStatus_Spawn.fBuildingSpawnGridCol;
}

void ABuildingBase::InitStatus(FBuildingStatus_Defense NewDefenseStatus, FBuildingStatus_Offense NewOffenseStatus, FBuildingStatus_Utility NewUtilityStatus, FBuildingStatus_Extra NewExtraStatus, FBuildingStatus_Spawn NewSpawnStatus, TArray<FObjectActionPattern> NewObjectActionPattern)
{
	SetDefenseStatus(NewDefenseStatus);
	SetOffenseStatus(NewOffenseStatus);
	SetUtilityStatus(NewUtilityStatus);
	SetExtraStatus(NewExtraStatus);
	SetSpawnStatus(NewSpawnStatus);
	SetBuildingActionPatterns(NewObjectActionPattern);
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

void ABuildingBase::SetBuildingActionPatterns(TArray<FObjectActionPattern> NewObjectActionPattern)
{
	this->ActionPattern = NewObjectActionPattern;
}

void ABuildingBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuildingBase, TeamNumber);
	DOREPLIFETIME(ABuildingBase, TeamColor);
}

float ABuildingBase::CalculateDamageBuilding(float Damage, int AttackTimes, E_OffenseType OffenseType)
{
	float damageMultiplier = DamageMatrix[static_cast<int>(OffenseType)][static_cast<int>(E_DefenseType::Building)];
	float finalDamage = ((((Damage / AttackTimes) * damageMultiplier) - BuildingStatus_Defense.fBuildingDefense) * AttackTimes);

	if (finalDamage < 0.5)
	{
		finalDamage = 0.5;
	}

	return finalDamage;
}

bool ABuildingBase::CustomTakeDamageBuilding(float Damage)
{
	BuildingStatus_Defense.fBuildingCurrentHealth -= Damage;

	BuildingHpBarUpdate.Broadcast(BuildingStatus_Defense.fBuildingCurrentHealth, BuildingStatus_Defense.fBuildingMaxHealth);

	if (BuildingStatus_Defense.fBuildingCurrentHealth <= 0)
	{
		this->isDead = true;


		OnBuildingDead.Broadcast(this);
		HpBarWidget->DestroyComponent();

		return false;
	}
	else
	{
		OnBuildingDamaged.Broadcast(this);
	}

	return true;
}
