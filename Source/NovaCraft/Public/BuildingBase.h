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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


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
	TArray<AActor*> CanSpawnObjects;

	UPROPERTY(VisibleAnywhere, Category = "Building Manage|Manage Value")
	FVector RallyPoint;

	UPROPERTY(EditAnywhere, Category = "Building Manage|Manage Value")
	TArray<FObjectActionPattern> ActionPattern;

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
	TArray <AActor*> GetCanSpawnObjects() const { return this->CanSpawnObjects; }

	UFUNCTION(BlueprintCallable, Category = "Building Status")
	int GetBuildingPriority() const { return this->BuildingStatus_Extra.fBuildingPriority; }

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

	// Function
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
