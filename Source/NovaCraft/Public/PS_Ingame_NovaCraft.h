// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_Ingame_NovaCraft.generated.h"

/**
 * 
 */
UCLASS()
class NOVACRAFT_API APS_Ingame_NovaCraft : public APlayerState
{
	GENERATED_BODY()
	
public:
	APS_Ingame_NovaCraft();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Player Manage|Manage Value|Resource")
	int PlayerGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Resource")
	int PlayerGas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Resource")
	int PlayerMaxPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Resource")
	int PlayerCurrentPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Camp")
	int GoldCampCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Camp")
	int GasCampCount = 0;

public:
	UFUNCTION(BlueprintCallable)
	void GainResourceTimerFunc();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CheckEnoughResource(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable)
	void GainGoldResource();

	UFUNCTION(BlueprintCallable)
	void GainGasResource();

	UFUNCTION(BlueprintCallable)
	void PaybackResource(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable)
	void DecreasePopulationWhenUnitDie();

	UFUNCTION(BlueprintCallable)
	void IncreasePopulationWhenUnitDie();

	UFUNCTION(BlueprintCallable)
	void AddGoldCampCount() { this->GoldCampCount++; };

	UFUNCTION(BlueprintCallable)
	void AddGasCampCount() { this->GasCampCount++; };

	UFUNCTION(BlueprintCallable)
	void SubGoldCampCount() { this->GoldCampCount--; };

	UFUNCTION(BlueprintCallable)
	void SubGasCampCount() { this->GasCampCount--; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Timer")
	FTimerHandle GainResourceTimer;

};
