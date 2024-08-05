// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_Ingame_NovaCraft.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"



APS_Ingame_NovaCraft::APS_Ingame_NovaCraft()
{
	PlayerGold = 100;
	PlayerGas = 0;
	PlayerMaxPopulation = 10;
	PlayerCurrentPopulation = 0;
}

void APS_Ingame_NovaCraft::BeginPlay()
{
	GetWorldTimerManager().SetTimer(GainResourceTimer, this, &APS_Ingame_NovaCraft::GainResourceTimerFunc, 2.0f, true);
}

void APS_Ingame_NovaCraft::GainResourceTimerFunc()
{
	GainGoldResource();
	GainGasResource();

	//UE_LOG(LogTemp, Warning, TEXT("%d / %d / %d / %d"), PlayerGold, PlayerGas, PlayerCurrentPopulation, PlayerMaxPopulation);
}

bool APS_Ingame_NovaCraft::CheckEnoughResource(int RqGold, int RqGas, int RqPop)
{
	if ((PlayerGold >= RqGold) && (PlayerGas >= RqGas) && ((PlayerCurrentPopulation + RqPop) <= PlayerMaxPopulation))
	{

		PlayerGold -= RqGold;


		if (RqGas > 0)
		{
			PlayerGas -= RqGas;
		}

		PlayerCurrentPopulation += RqPop;

		return true;

	}
	else 
	{
		return false;
	}

}

void APS_Ingame_NovaCraft::GainGoldResource()
{

	PlayerGold += 50 + GoldCampCount * 10;
}

void APS_Ingame_NovaCraft::GainGasResource()
{
	PlayerGas += 50+ GasCampCount * 20;
}

void APS_Ingame_NovaCraft::PaybackResource(int RqGold, int RqGas, int RqPop)
{
	PlayerGold += RqGold;
	PlayerGas += RqGas;
	PlayerCurrentPopulation -= RqPop;
}

void APS_Ingame_NovaCraft::IncreasePopulationWhenBuildingProduct()
{
	PlayerCurrentPopulation += 10;
}

void APS_Ingame_NovaCraft::DecreasePopulationWhenBuildingDestroy()
{
	PlayerCurrentPopulation -= 10;
}

void APS_Ingame_NovaCraft::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}