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

UCLASS()
class NOVACRAFT_API AActorEnums : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorEnums();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
