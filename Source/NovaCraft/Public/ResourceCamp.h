// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorEnums.h"
#include "UnitBase.h"
#include "GameFramework/Actor.h"
#include "ResourceCamp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTotalCountChanged, int, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCampStateChganged, E_CampState, NewState);

UCLASS()
class NOVACRAFT_API AResourceCamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceCamp();

	UPROPERTY(BlueprintAssignable)
	FOnTotalCountChanged OnTotalCountChanged;

	UPROPERTY(BlueprintAssignable)
	FOnCampStateChganged OnCampStateChganged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CampBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* DominationCollision;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* GaegeBar;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	UMaterialInstanceDynamic* DynamicMaterial;

private:
	UPROPERTY(VisibleAnywhere, Replicated, Category = "Manage|Value")
	E_CampState CampState = E_CampState::Neutrality;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	int PreDominationTeamNumber = -1;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	int DominationTeamNumber = -1;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	bool IsCompetition = false;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	TArray<int> CompetitionTeam = { 0,0,0,0 };

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Manage|Value")
	TArray<FLinearColor> PlayerTeamColor = {FLinearColor::Black,FLinearColor::Black ,FLinearColor::Black ,FLinearColor::Black };

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Manage|Value")
	int totalCount = 0;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Manage|Value", meta = (AllowPrivateAccess = true));
	FTimerHandle DominitionChargeTimer;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent)
	void PrintLogText();

	UFUNCTION()
	void DecreaseTeamCount(AUnitBase* DeadUnit);

	UFUNCTION(NetMulticast,Reliable)
	void SetTeamColor(FLinearColor NewTeamColor);

	UFUNCTION()
	void CheckCompetition(int ChangedTotalCount);

	UFUNCTION()
	int GetDominationTeamIndex();


	UFUNCTION()
	int CheckTeamCount();


	UFUNCTION()
	void CampProcess(E_CampState NewCampState);


	UFUNCTION()
	void ChargingProcess();

	UFUNCTION()
	void ChargingComplete();

	UFUNCTION()
	void NeutralityProcess();

	UFUNCTION()
	void CompetitionProcess();

	UFUNCTION()
	void RestorationComplete();

	UFUNCTION()
	void RestorationProcess();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RestorationCamp();

	UFUNCTION()
	void DominationProcess();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DominationComplete();

	UFUNCTION(NetMulticast,Reliable)
	void SetWidgetVisible(bool isVisible);

	// Getter
public:

	UFUNCTION(BlueprintCallable)
	int GetTotalCount() const { return this->totalCount; }


	UFUNCTION(BlueprintCallable)
	E_CampState GetCampState() const { return this->CampState; }

	UFUNCTION(BlueprintCallable)
	int GetDominationTeamNumber() const { return this->DominationTeamNumber; }

	UFUNCTION(BlueprintCallable)
	int GetPreDominationTeamNumber() const { return this->PreDominationTeamNumber; }

	// Setter
public:
	UFUNCTION(BlueprintCallable)
	void SetCampState(E_CampState NewState) { this->CampState = NewState; }

	UFUNCTION(BlueprintCallable)
	void SetDominationTeamNumber(int NewTeamNumber) { this->DominationTeamNumber = NewTeamNumber; }
};
