// Copyright Epic Games, Inc. All Rights Reserved.

#include "NovaCraftPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NovaCraftCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANovaCraftPlayerController::ANovaCraftPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	UnitSquadArray.SetNum(10);
	UnitSquadObjectDivide.SetNum(10);
}

void ANovaCraftPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ANovaCraftPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ANovaCraftPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ANovaCraftPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ANovaCraftPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ANovaCraftPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ANovaCraftPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ANovaCraftPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ANovaCraftPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ANovaCraftPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANovaCraftPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ANovaCraftPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ANovaCraftPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ANovaCraftPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ANovaCraftPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ANovaCraftPlayerController::SetUnitSquad(TArray<AActor*> NewSquad, int SquadIndex)
{
	if (UnitSquadArray.IsValidIndex(SquadIndex))
	{
		this->UnitSquadArray[SquadIndex].SetUnitSquad(NewSquad);

		for (AActor* Object : UnitSquadArray[SquadIndex].GetUnitSquad())
		{
			AUnitBase* MyUnit = Cast<AUnitBase>(Object);
			
			if (MyUnit)
			{
				MyUnit->OnUnitDead.AddDynamic(this, &ANovaCraftPlayerController::RemoveUnitFromSquad);
			}
			else
			{
				ABuildingBaseClass* MyBuilding = Cast<ABuildingBaseClass>(Object);

				if (MyBuilding)
				{
					MyBuilding->OnBuildingDead.AddDynamic(this, &ANovaCraftPlayerController::RemoveBuildingFromSquad);
				}
			}
		}
	}
	
}

void ANovaCraftPlayerController::RemoveUnitFromSquad(AUnitBase* DeadUnit)
{
	AActor* Unit = Cast<AActor>(DeadUnit);

	for (FUnitSquad& Squad : UnitSquadArray)
	{
		Squad.RemoveUnit(Unit);
	}
}

void ANovaCraftPlayerController::RemoveBuildingFromSquad(ABuildingBaseClass* DeadBuilding)
{
	AActor* Building = Cast<AActor>(DeadBuilding);

	for (FUnitSquad& Squad : UnitSquadArray)
	{
		Squad.RemoveUnit(Building);
	}
}

void ANovaCraftPlayerController::HoverBegin(bool Enemy)
{
	if (Enemy) {
		 // 적일 때 커서를 손 모양으로 변경
		CurrentMouseCursor = EMouseCursor::Hand;
	}
	else {
		  // 적이 아닐 때 조준 커서로 변경
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
}

void ANovaCraftPlayerController::HoverEnd()
{
	  // 마우스가 떠날 때 기본 커서로 변경
	CurrentMouseCursor = EMouseCursor::Default;
}


