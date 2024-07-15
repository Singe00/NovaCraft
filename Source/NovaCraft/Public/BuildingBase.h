// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingStatus_Defense.h"
#include "BuildingStatus_Offense.h"
#include "BuildingStatus_Utility.h"
#include "BuildingStatus_Extra.h"
#include "BuildingStatus_Spawn.h"
#include "ObjectActionPattern.h"
#include "BuildingBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBuildingHpBarUpdate, float, CurrentHp, float, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDead, ABuildingBase*, BuildingDestroy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDamaged, ABuildingBase*, DamagedBuilding);

UCLASS()
class NOVACRAFT_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	const float DamageMatrix[5][5] = {
		// None,     Small,    Medium,   Large,    Building
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f},    // None
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f},    // Normal
		{1.0f,      1.0f,     0.75f,     1.25f,    2.0f},    // Explosive
		{1.0f,      1.5f,    0.75f,     0.5f,     0.5f},   // Concussive
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f}     // Spell
	};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FBuildingHpBarUpdate BuildingHpBarUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingDamaged OnBuildingDamaged;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingDead OnBuildingDead;

	//Components
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* BuildingBaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* SelectedDecal;

	// All Common Status Under Here

	// Manage Value
public:
	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	FName DataTableRowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	int TeamNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	FLinearColor TeamColor;


	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	TArray<TSubclassOf<AUnitBase>> CanSpawnObjects;

	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Manage Value")
	FVector RallyPoint;

	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Manage Value")
	AActor* RallyActor;

	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	TArray<FObjectActionPattern> ActionPattern;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	bool isDead = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	bool isProducting = false;


protected:
	// Defence Status
	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Building Status|Defense Status")
	FBuildingStatus_Defense BuildingStatus_Defense;

	// Offense Status
	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Building Status|Offense Status")
	FBuildingStatus_Offense BuildingStatus_Offense;

	//Utility Status
	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Building Status|Utility Status")
	FBuildingStatus_Utility BuildingStatus_Utility;

	// Extra Status
	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Building Status|Extra Status")
	FBuildingStatus_Extra BuildingStatus_Extra;

	// Spawn Status
	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Building Status|Spawn Status")
	FBuildingStatus_Spawn BuildingStatus_Spawn;

	// Getter
public:
	UFUNCTION(BlueprintCallable)
	FName GetBuildingDataTableRowName() const { return this->DataTableRowName; }

	UFUNCTION(BlueprintCallable)
	FBuildingStatus_Defense GetBuildingStatus_Defense() const { return this->BuildingStatus_Defense; }

	UFUNCTION(BlueprintCallable)
	FBuildingStatus_Offense GetBuildingStatus_Offense() const { return this->BuildingStatus_Offense; }

	UFUNCTION(BlueprintCallable)
	FBuildingStatus_Utility GetBuildingStatus_Utility() const { return this->BuildingStatus_Utility; }

	UFUNCTION(BlueprintCallable)
	FBuildingStatus_Extra GetBuildingStatus_Extra() const { return this->BuildingStatus_Extra; }

	UFUNCTION(BlueprintCallable)
	FBuildingStatus_Spawn GetBuildingStatus_Spawn() const { return this->BuildingStatus_Spawn; }

	UFUNCTION(BlueprintCallable, Category = "Building Manage")
	void GetBuildSpawnGridValue(
		int& RowValue,
		int& ColValue) const;

	UFUNCTION(BlueprintCallable, Category = "Building Manage")
	TArray<FObjectActionPattern> GetBuildingActionPatterns() const { return this->ActionPattern; }

	UFUNCTION(BlueprintCallable, Category = "Building Manage")
	TArray <TSubclassOf<AUnitBase>> GetCanSpawnObjects() const { return this->CanSpawnObjects; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	int GetBuildingPriority() const { return this->BuildingStatus_Extra.fBuildingPriority; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	FVector GetBuildingRallyPoint() const { return this->RallyPoint; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	AActor* GetBuildingRallyActor() const { return this->RallyActor; }
	// Setter
public:
	UFUNCTION(BlueprintCallable)
	void InitStatus(FBuildingStatus_Defense NewDefenseStatus, FBuildingStatus_Offense NewOffenseStatus, FBuildingStatus_Utility NewUtilityStatus, FBuildingStatus_Extra NewExtraStatus, FBuildingStatus_Spawn NewSpawnStatus, TArray<FObjectActionPattern> NewObjectActionPattern);

	UFUNCTION(BlueprintCallable)
	void SetDefenseStatus(FBuildingStatus_Defense NewDefenseStatus);

	UFUNCTION(BlueprintCallable)
	void SetOffenseStatus(FBuildingStatus_Offense NewOffenseStatus);

	UFUNCTION(BlueprintCallable)
	void SetUtilityStatus(FBuildingStatus_Utility NewUtilityStatus);

	UFUNCTION(BlueprintCallable)
	void SetExtraStatus(FBuildingStatus_Extra NewExtraStatus);

	UFUNCTION(BlueprintCallable)
	void SetSpawnStatus(FBuildingStatus_Spawn NewSpawnStatus);

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	void SetBuildingActionPatterns(TArray<FObjectActionPattern> NewObjectActionPattern);

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	void SetBuildingRallyPoint(FVector NewRallyPoint) { this->RallyPoint = NewRallyPoint; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	void SetBuildingRallyActor(AActor* NewRallyActor) { this->RallyActor = NewRallyActor; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	void SetIsProducting(bool NewProducting) { this->isProducting = NewProducting; }
	// Function
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	float CalculateDamageBuilding(float Damage, int AttackTimes, E_OffenseType OffenseType);

	UFUNCTION(BlueprintCallable)
	bool CustomTakeDamageBuilding(float Damage);

};
