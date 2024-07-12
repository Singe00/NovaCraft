// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Public/UnitBase.h"
#include "NovaCraftPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FUnitSquad
{
	GENERATED_BODY()
private:
	TArray<AActor*> Units;

public:

	TArray<AActor*> GetUnitSquad() const { return this->Units; }

	void SetUnitSquad(TArray<AActor*> NewUnitSquad) { this->Units = NewUnitSquad; }

	void RemoveUnit(AActor* DeadUnit)
	{
		Units.Remove(DeadUnit);
	}
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ANovaCraftPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANovaCraftPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;

	UPROPERTY(VisibleAnywhere, Category = "Unit Squad")
	TArray<FUnitSquad> UnitSquadArray;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	//Getter
public:

	UFUNCTION(BlueprintCallable)
	TArray<AActor*>  GetUnitSquad(int SquadIndex) const { return this->UnitSquadArray[SquadIndex].GetUnitSquad(); }


	//Setter
public:
	UFUNCTION(BlueprintCallable)
	void SetUnitSquad(TArray<AActor*>  NewSquad, int SquadIndex);

	UFUNCTION(BlueprintCallable)
	void RemoveUnitFromSquad(AUnitBase* DeadUnit);
};


