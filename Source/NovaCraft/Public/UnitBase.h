// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitStatus_Defense.h"
#include "UnitStatus_Offense.h"
#include "UnitStatus_Utility.h"
#include "UnitStatus_Extra.h"
#include "UnitStatus_Spawn.h"
#include "UnitBase.generated.h"

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

	// All Common Status Under Here

	// Manage Value
public:
	UPROPERTY(EditAnywhere, Category = "Unit Manage|Manage Value")
	FName DataTableRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Unit Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	int TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Unit Manage|Manage Value", meta = (ExposeOnSpawn = "true"))
	FLinearColor TeamColor;

protected:
	// Defence Status
	UPROPERTY(VisibleAnywhere, Category = "Unit Manage|Unit Status|Defense Status")
	FUnitStatus_Defense UnitStatus_Defense;

	// Offense Status
	UPROPERTY(VisibleAnywhere, Category = "Unit Manage|Unit Status|Offense Status")
	FUnitStatus_Offense UnitStatus_Offense;

	//Utility Status
	UPROPERTY(VisibleAnywhere, Category = "Unit Manage|Unit Status|Utility Status")
	FUnitStatus_Utility UnitStatus_Utility;

	// Extra Status
	UPROPERTY(VisibleAnywhere, Category = "Unit Manage|Unit Status|Extra Status")
	FUnitStatus_Extra UnitStatus_Extra;

	// Spawn Status
	UPROPERTY(VisibleAnywhere, Category = "Unit Manage|Unit Status|Spawn Status")
	FUnitStatus_Spawn UnitStatus_Spawn;


// Getter
public:
	UFUNCTION(BlueprintCallable)
	FName GetUnitDataTableRowName() const { return this->DataTableRowName; }

	UFUNCTION(BlueprintCallable)
	FUnitStatus_Defense GetUnitStatus_Defense() const { return this->UnitStatus_Defense; }

	UFUNCTION(BlueprintCallable)
	FUnitStatus_Offense GetUnitStatus_Offense() const { return this->UnitStatus_Offense; }

	UFUNCTION(BlueprintCallable)
	FUnitStatus_Utility GetUnitStatus_Utility() const { return this->UnitStatus_Utility; }

	UFUNCTION(BlueprintCallable)
	FUnitStatus_Extra GetUnitStatus_Extra() const { return this->UnitStatus_Extra; }

	UFUNCTION(BlueprintCallable)
	FUnitStatus_Spawn GetUnitStatus_Spawn() const { return this->UnitStatus_Spawn; }


// Setter
public:
	UFUNCTION(BlueprintCallable)
	void InitStatus(FUnitStatus_Defense NewDefenseStatus, FUnitStatus_Offense NewOffenseStatus, FUnitStatus_Utility NewUtilityStatus, FUnitStatus_Extra NewExtraStatus, FUnitStatus_Spawn NewSpawnStatus);

	UFUNCTION(BlueprintCallable)
	void SetDefenseStatus(FUnitStatus_Defense NewDefenseStatus);

	UFUNCTION(BlueprintCallable)
	void SetOffenseStatus(FUnitStatus_Offense NewOffenseStatus);

	UFUNCTION(BlueprintCallable)
	void SetUtilityStatus(FUnitStatus_Utility NewUtilityStatus);

	UFUNCTION(BlueprintCallable)
	void SetExtraStatus(FUnitStatus_Extra NewExtraStatus);

	UFUNCTION(BlueprintCallable)
	void SetSpawnStatus(FUnitStatus_Spawn NewSpawnStatus);

	// Function
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
