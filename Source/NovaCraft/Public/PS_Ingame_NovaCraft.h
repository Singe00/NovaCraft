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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	int PlayerGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	int PlayerGas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	int PlayerMaxPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	int PlayerCurrentPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Camp")
	int GoldCampCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Camp")
	int GasCampCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	int PlayerBuildingCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Resource")
	bool IsPlayerEliminated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Tech")
	int Tech0OffenceLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Tech")
	int Tech0DefenceLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Tech")
	int Tech1OffenceLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Tech")
	int Tech1DefenceLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Player Manage|Manage Value|Tech")
	int BuildingDefenceLevel = 0;

public:
	UFUNCTION()
	void GainResourceTimerFunc();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool CheckEnoughResourceSpawnUnit(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CheckEnoughResourceSpawnBuilding(int RqGold, int RqGas);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CheckEnoughResourceUnitUpgrade(int RqGold, int RqGas);

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void SpendResourceSpawnBuilding(int RqGold, int RqGas);

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void SpendResourceSpawnUnit(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SpendResourceUnitUpgrade(int RqGold, int RqGas);

	UFUNCTION(BlueprintCallable)
	void GainGoldResource(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable)
	void GainGasResource();

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void PaybackResource(int RqGold, int RqGas, int RqPop);

	UFUNCTION(BlueprintCallable)
	void IncreasePopulationWhenBuildingProduct();

	UFUNCTION(BlueprintCallable)
	void DecreasePopulationWhenBuildingDestroy();

	UFUNCTION(BlueprintCallable)
	void AddGoldCampCount();

	UFUNCTION(BlueprintCallable)
	void AddGasCampCount() { this->GasCampCount++; };

	UFUNCTION(BlueprintCallable)
	void SubGoldCampCount();

	UFUNCTION(BlueprintCallable)
	void SubGasCampCount() { this->GasCampCount--; };

	UFUNCTION(BlueprintCallable)
	void DecreasePopulationWhenUnitDead(int UnitPop);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateResourceWidget();

	UFUNCTION(Client, Reliable)
	void UpdateResourceClient(int RqGold,int RqGas);
	void UpdateResourceClient_Implementation(int RqGold, int RqGas);

	UFUNCTION(Server,Reliable,WithValidation)
	void Server_SetPlayerEliminated();

	UFUNCTION()
	void SetPlayerEliminated();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Manage|Manage Value|Timer")
	FTimerHandle GainResourceTimer;


	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;


//Fog
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="MaterialInstance")
	UMaterialInstanceDynamic *MaterialInstance01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialInstance")
	UMaterialInstanceDynamic *MaterialInstance02;

};
