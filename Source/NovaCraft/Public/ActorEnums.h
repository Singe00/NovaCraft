// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorEnums.generated.h"

UENUM(BlueprintType)
enum class E_UnitState : uint8
{
	Stop UMETA(DisplayName = "Stop"),
	Move UMETA(DisplayName = "Move"),
	Hold UMETA(DisplayName = "Hold"),
	Patrol UMETA(DisplayName = "Patrol"),
	Attack UMETA(DisplayName = "Attack"),
	Follow UMETA(DisplayName = "Follow"),
	Marching UMETA(DisplayName = "Marching"),
	Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class E_DefenseType : uint8
{
	None UMETA(DisplayName = "None"),
	Small UMETA(DisplayName = "Small"),
	Medium UMETA(DisplayName = "Medium"),
	Large UMETA(DisplayName = "Large"),
	Building UMETA(DisplayName = "Building"),
};


UENUM(BlueprintType)
enum class E_OffenseType : uint8
{
	None UMETA(DisplayName = "None"),
	Normal UMETA(DisplayName = "Normal"),
	Explosive UMETA(DisplayName = "Explosive"),
	Concussive UMETA(DisplayName = "Concussive"),
	Spell UMETA(DisplayName = "Spell"),
};

UENUM(BlueprintType)
enum class E_RaceType : uint8
{
	None UMETA(DisplayName = "None"),
	RaceA UMETA(DisplayName = "RaceA"),
	RaceB UMETA(DisplayName = "RaceB"),
	RaceC UMETA(DisplayName = "RaceC"),
};

UENUM(BlueprintType) //Delete
enum class E_UnitType : uint8
{
	Ground UMETA(DisplayName = "Ground"),
	Air UMETA(DisplayName = "Air"),
};

UENUM(BlueprintType)
enum class E_ObjectMoveType : uint8
{
	Ground UMETA(DisplayName = "Ground"),
	Air UMETA(DisplayName = "Air"),
};

UENUM(BlueprintType)
enum class E_AISense : uint8
{
	None UMETA(DisplayName = "None"),
	Sight UMETA(DisplayName = "Sight"),
	Damage UMETA(DisplayName = "Damage"),
};

UENUM(BlueprintType)
enum class E_BuildingMoveType : uint8
{
	Ground UMETA(DisplayName = "Ground"),
	Air UMETA(DisplayName = "Air"),

};


UENUM(BlueprintType)
enum class E_BuildingType : uint8
{
	None UMETA(DisplayName = "None"),
	Main UMETA(DisplayName = "Main"),
	Unit UMETA(DisplayName = "Unit"),
	Upgrade UMETA(DisplayName = "Upgrade"),
	Population UMETA(DisplayName = "Population"),

};

UENUM(BlueprintType)
enum class E_ObjectType : uint8
{
	None UMETA(DisplayName = "None"),
	Unit UMETA(DisplayName = "Unit"),
	Building UMETA(DisplayName = "Building"),
};

UENUM(BlueprintType)
enum class E_CampState : uint8
{
	None UMETA(DisplayName = "None"),
	Neutrality UMETA(DisplayName = "Neutrality"),
	Competition UMETA(DisplayName = "Competition"),
	Charging UMETA(DisplayName = "Charging"),
	Restoration UMETA(DisplayName = "Restoration"),
	Domination UMETA(DisplayName = "Domination"),
};

UCLASS()
class NOVACRAFT_API AActorEnums : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorEnums();


};
