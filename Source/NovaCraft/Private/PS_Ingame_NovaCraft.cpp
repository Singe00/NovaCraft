// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_Ingame_NovaCraft.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "../NovaCraftPlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"



APS_Ingame_NovaCraft::APS_Ingame_NovaCraft()
{
	PlayerGold = 100;
	PlayerGas = 0;
	PlayerMaxPopulation = 10;
	PlayerCurrentPopulation = 0;
}

void APS_Ingame_NovaCraft::BeginPlay()
{
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(GainResourceTimer, this, &APS_Ingame_NovaCraft::GainResourceTimerFunc, 2.0f, true);
	}
	

	//fog
	

}

void APS_Ingame_NovaCraft::GainResourceTimerFunc_Implementation()
{
	GainGoldResource();
	GainGasResource();

	UpdateResourceWidget();
}

bool APS_Ingame_NovaCraft::CheckEnoughResourceSpawnUnit(int RqGold, int RqGas, int RqPop)
{
	if ((PlayerGold >= RqGold) && (PlayerGas >= RqGas) && ((PlayerCurrentPopulation + RqPop) <= PlayerMaxPopulation))
	{

		PlayerGold -= RqGold;


		if (RqGas > 0)
		{
			PlayerGas -= RqGas;
		}

		PlayerCurrentPopulation += RqPop;

		UpdateResourceWidget();


		return true;

	}
	else 
	{
		return false;
	}

}

bool APS_Ingame_NovaCraft::CheckEnoughResourceSpawnBuilding(int RqGold, int RqGas)
{

	if ((PlayerGold >= RqGold) && (PlayerGas >= RqGas))
	{

		return true;

	}
	else
	{
		return false;
	}
}

void APS_Ingame_NovaCraft::SpendResourceSpawnBuilding(int RqGold, int RqGas)
{

	PlayerGold -= RqGold;


	if (RqGas > 0)
	{
		PlayerGas -= RqGas;
	}


	UpdateResourceWidget();
}



void APS_Ingame_NovaCraft::GainGoldResource()
{

	PlayerGold += 50 + GoldCampCount * 100000;

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

	PlayerMaxPopulation += 10;

	if (PlayerMaxPopulation > 100)
	{
		PlayerMaxPopulation = 100;
	}


	UpdateResourceWidget();
}

void APS_Ingame_NovaCraft::DecreasePopulationWhenBuildingDestroy()
{

	PlayerMaxPopulation -= 10;

	if (PlayerMaxPopulation < 10)
	{
		PlayerMaxPopulation = 10;
	}

	UpdateResourceWidget();
}

void APS_Ingame_NovaCraft::SubGoldCampCount()
{
	this->GoldCampCount--;
}



void APS_Ingame_NovaCraft::AddGoldCampCount()
{
	this->GoldCampCount++;
}

void APS_Ingame_NovaCraft::UpdateResourceWidget_Implementation()
{
}

void APS_Ingame_NovaCraft::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APS_Ingame_NovaCraft, PlayerGold);
	DOREPLIFETIME(APS_Ingame_NovaCraft, PlayerGas);
	DOREPLIFETIME(APS_Ingame_NovaCraft, PlayerMaxPopulation);
	DOREPLIFETIME(APS_Ingame_NovaCraft, PlayerCurrentPopulation);
	DOREPLIFETIME(APS_Ingame_NovaCraft, GoldCampCount);
	DOREPLIFETIME(APS_Ingame_NovaCraft, GasCampCount);
}