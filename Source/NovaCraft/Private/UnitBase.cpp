// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitBase.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "../NovaCraftPlayerController.h"
#include "PS_Ingame_NovaCraft.h"
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
	
	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/00_Work/Common/Widget/CommonObject/WB_CustomHpBar'_C"));

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidget"));

	if (UW.Succeeded())
	{
		HpBarWidget->SetupAttachment(RootComponent);
		HpBarWidget->SetWidgetClass(UW.Class);
		HpBarWidget->SetDrawSize(FVector2D(100, 10));
		HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarWidget->SetDrawAtDesiredSize(true);
	}



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


bool AUnitBase::IfWillDie(float damage)
{
	float temp = UnitStatus_Defense.fCurrentHealth - damage;

	if (temp <= 0)
	{
		return true;
	}
	else {
		return false;
	}

}

void AUnitBase::InitStatus(FUnitStatus_Defense NewDefenseStatus, FUnitStatus_Offense NewOffenseStatus, FUnitStatus_Utility NewUtilityStatus, FUnitStatus_Extra NewExtraStatus, FUnitStatus_Spawn NewSpawnStatus, TArray<FObjectActionPattern> NewObjectActionPattern)
{
	SetDefenseStatus(NewDefenseStatus);
	SetOffenseStatus(NewOffenseStatus);
	SetUtilityStatus(NewUtilityStatus);
	SetExtraStatus(NewExtraStatus);
	SetSpawnStatus(NewSpawnStatus);
	SetUnitActionPatterns(NewObjectActionPattern);

	auto movement = GetCharacterMovement();
	movement->MaxWalkSpeed = this->UnitStatus_Utility.fMoveSpeed;
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

void AUnitBase::SetAirUnitMoveLocation(bool MoveState, FVector TargetLocation)
{
	AirUnitMovement = MoveState;
	AirUnitMoveTargetLocation = TargetLocation;
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
		std::lock_guard<std::mutex> lock(UnitDeadMutex);

		if (!isDead)
		{
			this->isDead = true;


			HpBarWidget->SetVisibility(false);

			OnUnitDead.Broadcast(this);

			return false;
		}
	}
	else
	{
		OnUnitDamaged.Broadcast(this);
	}

	return true;
}

UAnimMontage* AUnitBase::GetRandomMontage(TArray<class UAnimMontage*> Montages)
{

	if (Montages.Num() == 0)
	{
		return nullptr;
	}

	int32 RandomIndex = FMath::RandRange(0, Montages.Num() - 1);
	return Montages[RandomIndex];
}

USoundWave* AUnitBase::GetRandomSound(TArray<class USoundWave*> Sounds)
{
	if (Sounds.Num() == 0)
	{
		return nullptr;
	}

	int32 RandomIndex = FMath::RandRange(0, Sounds.Num() - 1);
	return Sounds[RandomIndex];
}

void AUnitBase::FlyUnitMoveToLocation(float DeltaTime)
{
	if (AirUnitMovement)
	{
		FVector CurrentLocation = this->GetActorLocation();

		FVector Direction = (AirUnitMoveTargetLocation - CurrentLocation).GetSafeNormal2D();

		FVector MovementVector = GetMoveSpeed() * Direction * DeltaTime;

		FVector NewLocation = CurrentLocation + MovementVector;
		NewLocation.Z = CurrentLocation.Z;

		// Set the new location of the unit
		this->SetActorLocation(NewLocation);

		if (FVector::Dist2D(CurrentLocation, AirUnitMoveTargetLocation) <= 50.0f)
		{
			// Stop movement
			AirUnitMovement = false;
			FlyUnitMovementFinish();
		}
	}

}

void AUnitBase::FlyUnitPatrol(float DeltaTime)
{
}

void AUnitBase::FlyUnitInit()
{
	if (this->UnitStatus_Defense.fUnitType == E_UnitType::Air)
	{
		auto movement = GetCharacterMovement();

		movement->GravityScale = 0.0f;

		GetMesh()->SetEnableGravity(false);
		GetCapsuleComponent()->SetEnableGravity(false);

		FVector CurrentLocation = GetActorLocation();

		this->SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, 250));
	}
}

void AUnitBase::SightSensedObjectProcess(AActor* SensedActor)
{
	if (SensedActor && !SensingObject.Contains(SensedActor))
	{
		AUnitBase* SenseUnit = Cast<AUnitBase>(SensedActor);

		if (SenseUnit)
		{
			if (SenseUnit->TeamNumber != this->TeamNumber)
			{
				if ((SenseUnit->GetUnitType() == E_UnitType::Ground && this->GetUnitCanGroundAttack()) || (SenseUnit->GetUnitType() == E_UnitType::Air && this->GetUnitCanAirAttack()))
				{
					SensingObject.AddUnique(SensedActor);
					SenseUnit->OnUnitDead.AddDynamic(this, &AUnitBase::RemoveUnitFromSO);


					CustomSenseInSight();
				}
			}
		}
		else
		{
			ABuildingBaseClass* SenseBuilding = Cast<ABuildingBaseClass>(SensedActor);

			if (SenseBuilding)
			{
				if (SenseBuilding->TeamNumber != this->TeamNumber)
				{
					SensingObject.AddUnique(SensedActor);
					SenseBuilding->OnBuildingDead.AddDynamic(this, &AUnitBase::RemoveBuildingFromSO);


					CustomSenseInSight();
				}
			}
		}
	}
}

void AUnitBase::SightSensedOutObjectProcess(AActor* SensedActor)
{

	if (SensedActor)
	{
		SensingObject.Remove(SensedActor);

		AUnitBase* SenseUnit = Cast<AUnitBase>(SensedActor);

		if (SenseUnit)
		{
			SenseUnit->OnUnitDead.RemoveDynamic(this, &AUnitBase::RemoveUnitFromSO);
		}
		else
		{
			ABuildingBaseClass* SenseBuilding = Cast<ABuildingBaseClass>(SensedActor);

			if (SenseBuilding)
			{
				SenseBuilding->OnBuildingDead.RemoveDynamic(this, &AUnitBase::RemoveBuildingFromSO);
			}
		}
	}
}



void AUnitBase::FlyUnitMovementFinish_Implementation()
{

}

void AUnitBase::RemoveUnitFromSO(AUnitBase* DeadUnit)
{
	AActor* Unit = Cast<AActor>(DeadUnit);
	
	if (SensingObject.Contains(Unit))
	{
		SensingObject.Remove(Unit);
	}
}

void AUnitBase::RemoveBuildingFromSO(ABuildingBaseClass* DeadBuilding)
{
	AActor* Building = Cast<AActor>(DeadBuilding);

	if (SensingObject.Contains(Building))
	{
		SensingObject.Remove(Building);
	}
}

AActor* AUnitBase::GetNearestObject()
{
	if (SensingObject.IsEmpty())
	{
		return nullptr;
	}

	AActor* NearestObject = nullptr;
	float NearestDist = FLT_MAX;

	FVector StandardLocation = this->GetActorLocation();
	StandardLocation.Z = 0.0f;

	for (AActor* Object : SensingObject)
	{
		if (Object)
		{
			FVector ObjectLocation = Object->GetActorLocation();
			ObjectLocation.Z = 0.0f;

			float BetweenDist = FVector::DistSquared(StandardLocation, ObjectLocation);

			if (BetweenDist < NearestDist)
			{
				NearestDist = BetweenDist;
				NearestObject = Object;
			}
		}
	}

	return NearestObject;

}

void AUnitBase::CustomSenseInSight_Implementation()
{
}
