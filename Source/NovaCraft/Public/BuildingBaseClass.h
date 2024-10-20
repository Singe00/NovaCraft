// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BuildingStatus_Defense.h"
#include "BuildingStatus_Offense.h"
#include "BuildingStatus_Utility.h"
#include "BuildingStatus_Extra.h"
#include "BuildingStatus_Spawn.h"
#include "ObjectActionPattern.h"
#include "mutex"
#include "BuildingBaseClass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDead, ABuildingBaseClass*, BuildingDestroy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingDamaged, ABuildingBaseClass*, DamagedBuilding);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBuildingHpBarUpdate, float, CurrentHp, float, MaxHp);

UCLASS()
class NOVACRAFT_API ABuildingBaseClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABuildingBaseClass();

	const float DamageMatrix[5][5] = {
		// None,     Small,    Medium,   Large,    Building
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f},    // None
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f},    // Normal
		{1.0f,      1.0f,     0.75f,     1.25f,    2.0f},    // Explosive
		{1.0f,      1.5f,    0.75f,     0.5f,     0.5f},   // Concussive
		{1.0f,      1.0f,     1.0f,     1.0f,     1.0f}     // Spell
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Delegate
public:

	UPROPERTY(BlueprintAssignable)
	FBuildingHpBarUpdate BuildingHpBarUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingDamaged OnBuildingDamaged;

	UPROPERTY(BlueprintAssignable)
	FOnBuildingDead OnBuildingDead;

	//Components
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDecalComponent* SelectedDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	class UWidgetComponent* HpBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* OverlapCollision;

	// All Common Status Under Here

	// Manage Value
public:
	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	FName DataTableRowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	int TeamNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	FLinearColor TeamColor;

	// Attack Montage (사망 애니메이션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Anim Montages")
	TArray<class UAnimMontage*> DeadMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	TArray<TSubclassOf<AActor>> CanSpawnObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	TArray<FName> CanSpawnObjectsIndex;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Building Manage|Manage Value")
	FVector RallyPoint;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Building Manage|Manage Value")
	AActor* RallyActor;

	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	TArray<FObjectActionPattern> ActionPattern;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	bool isDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	bool isSelected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Building Manage|Manage Value")
	bool isProducting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Manage Value")
	TArray<int> ProductingArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Manage Value")
	TArray<class UMaterialInstance*> BuildingMaterials;

	// Attack Sound  (공격 사운드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Sounds")
	TArray<class USoundWave*> AttackSounds;

	// Death Sound  (사망 사운드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Sounds")
	TArray<class USoundWave*> DeathSounds;

	// Move Sound  (이동 사운드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Sounds")
	TArray<class USoundWave*> MoveSounds;

	// Select Sound  (선택 사운드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Manage|Sounds")
	TArray<class USoundWave*> SelectSounds;

	std::mutex BuildingDeadMutex;


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
	TArray <TSubclassOf<AActor>> GetCanSpawnObjects() const { return this->CanSpawnObjects; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	int GetBuildingPriority() const { return this->BuildingStatus_Extra.fBuildingPriority; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	FVector GetBuildingRallyPoint() const { return this->RallyPoint; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	AActor* GetBuildingRallyActor() const { return this->RallyActor; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	E_BuildingType GetBuildingType() const { return this->BuildingStatus_Extra.fBuildingType; }

	UFUNCTION(BlueprintCallable)
	USkeletalMesh* GetBuildingBaseMeshObject() const { return this->GetMesh()->GetSkeletalMeshAsset(); }

	UFUNCTION(BlueprintCallable)
	E_BuildingMoveType GetBuildingMoveTpye() const { return this->BuildingStatus_Defense.fBuildingMoveType; }

	UFUNCTION(BlueprintCallable)
	float GetBuildingCurrentHp() const { return this->BuildingStatus_Defense.fBuildingCurrentHealth; }

	UFUNCTION(BlueprintCallable)
	float GetBuildingMaxHp() const { return this->BuildingStatus_Defense.fBuildingMaxHealth; }

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetBuilding2DImage() const { return this->BuildingStatus_Extra.fBuilding2DImage; }

	UFUNCTION(BlueprintCallable)
	bool GetProductingIsFull() const;

	UFUNCTION(BlueprintCallable)
	bool IfWillDie(float damage);

	UFUNCTION(BlueprintCallable)
	int GetBuildingTechLevel() const { return BuildingStatus_Spawn.fBuildingSpawnTechLevel; }
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

	UFUNCTION(BlueprintCallable)
	void AddProductingUnit(int SpawnIndex);

	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetRandomMontage(TArray<class UAnimMontage*> Montages);

	UFUNCTION(BlueprintCallable)
	USoundWave* GetRandomSound(TArray<class USoundWave*> Sounds);
};
