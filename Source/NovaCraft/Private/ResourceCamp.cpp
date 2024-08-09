// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCamp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstance.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AResourceCamp::AResourceCamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;

	CampBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CampBody"));
	RootComponent = CampBodyMesh;
	CampBodyMesh->SetIsReplicated(true);

	DominationCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DominationZone"));
	DominationCollision->SetupAttachment(CampBodyMesh);


	DominationCollision->OnComponentBeginOverlap.AddDynamic(this, &AResourceCamp::OnComponentBeginOverlap);
	DominationCollision->OnComponentEndOverlap.AddDynamic(this, &AResourceCamp::OnComponentEndOverlap);

	this->OnTotalCountChanged.AddDynamic(this, &AResourceCamp::CheckCompetition);
	this->OnCampStateChganged.AddDynamic(this, &AResourceCamp::CampProcess);
}

// Called when the game starts or when spawned
void AResourceCamp::BeginPlay()
{
	Super::BeginPlay();

	static FString MI_Path = "/Game/00_Work/WorkPlace/SiWan/Camp/Material/M_Domination_Inst";
	UMaterialInstance* MI_TeamColor = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInterface::StaticClass(), this, *MI_Path));

	if (MI_TeamColor != nullptr)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MI_TeamColor, this);

		if (DynamicMaterial)
		{
			CampBodyMesh->SetMaterial(0, DynamicMaterial);

			DynamicMaterial->SetVectorParameterValue(TEXT("TeamColor"), FVector4(0.1f, 0.1f, 0.1f, 1.0f));
		}

	}

}

// Called every frame
void AResourceCamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResourceCamp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AResourceCamp, totalCount);
	DOREPLIFETIME(AResourceCamp, PlayerTeamColor);
	DOREPLIFETIME(AResourceCamp, CampState);
}

void AResourceCamp::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		AUnitBase* CompetitionUnit = Cast<AUnitBase>(OtherActor);

		if (CompetitionUnit)
		{
			CompetitionTeam[CompetitionUnit->TeamNumber] += 1;
			PlayerTeamColor[CompetitionUnit->TeamNumber] = CompetitionUnit->TeamColor;

			this->totalCount += 1;

			OnTotalCountChanged.Broadcast(this->totalCount);
		}
	}
}

void AResourceCamp::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		AUnitBase* CompetitionUnit = Cast<AUnitBase>(OtherActor);

		if (CompetitionUnit)
		{
			DecreaseTeamCount(CompetitionUnit);

			OnTotalCountChanged.Broadcast(this->totalCount);
		}
	}
}

void AResourceCamp::DecreaseTeamCount(AUnitBase* DeadUnit)
{
	if (DeadUnit)
	{
		if (this->CompetitionTeam[DeadUnit->TeamNumber] > 0)
		{
			this->CompetitionTeam[DeadUnit->TeamNumber] -= 1;
			this->totalCount-=1;

			OnTotalCountChanged.Broadcast(this->totalCount);

			UE_LOG(LogTemp, Warning, TEXT("Decrease"));

		}
	}
}

void AResourceCamp::SetTeamColor_Implementation(FLinearColor NewTeamColor)
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(TEXT("TeamColor"), NewTeamColor);
	}
}

void AResourceCamp::CheckCompetition(int ChangedTotalCount)
{

	if (ChangedTotalCount > 0)
	{
		// 경쟁 상태인지 확인해야함

		if (CheckTeamCount() == 1)
		{
			if (GetCampState() == E_CampState::Neutrality || GetCampState() == E_CampState::Competition)
			{
				// 점령 시작
				SetCampState(E_CampState::Charging);

				OnCampStateChganged.Broadcast(this->CampState);
			}
			else if (GetCampState() == E_CampState::Domination)
			{
				// 수복 시작
				SetCampState(E_CampState::Restoration);

				OnCampStateChganged.Broadcast(this->CampState);
			}

		}
		else if (CheckTeamCount() == 2)
		{
			// 점령 상태 중단
			SetCampState(E_CampState::Competition);

			OnCampStateChganged.Broadcast(this->CampState);
		}
	}
	else 
	{
		if (GetCampState() == E_CampState::Charging)
		{
			// 점령 시작
			SetCampState(E_CampState::Neutrality);

			OnCampStateChganged.Broadcast(this->CampState);
		}
	}


}

int AResourceCamp::GetDominationTeamIndex()
{
	int tmp = -1;

	for (int i = 0 ;i<4;i++)
	{
		if (CompetitionTeam[i] > 0)
		{
			tmp = i;
			break;
		}
	}
	return tmp;
}

int AResourceCamp::CheckTeamCount()
{
	int count = 0;

	for (int c : CompetitionTeam)
	{
		if (c > 0)
		{
			count++;
		}
	}

	return count;
}

void AResourceCamp::CampProcess(E_CampState NewCampState)
{
	PrintLogText();

	switch (NewCampState)
	{
	case E_CampState::None:
		break;
	case E_CampState::Neutrality:
		break;
	case E_CampState::Competition:
		CompetitionProcess();
		break;
	case E_CampState::Charging:
		GetWorldTimerManager().SetTimer(DominitionChargeTimer, this, &AResourceCamp::ChargingComplete, 4.0f,false);
		break;
	case E_CampState::Restoration:
		RestorationProcess();
		break;
	case E_CampState::Domination:
		DominationProcess();
		break;
	default:
		break;
	}
}

void AResourceCamp::ChargingComplete()
{
	if (GetDominationTeamIndex() >= 0)
	{
		SetCampState(E_CampState::Domination);
		SetTeamColor(PlayerTeamColor[GetDominationTeamIndex()]);
		SetDominationTeamNumber(GetDominationTeamIndex());
	}

}

void AResourceCamp::CompetitionProcess()
{
	GetWorldTimerManager().ClearTimer(DominitionChargeTimer);
}

void AResourceCamp::RestorationComplete()
{
	SetCampState(E_CampState::Charging);
	SetTeamColor(FLinearColor::Black);
	SetDominationTeamNumber(-1);

	GetWorldTimerManager().SetTimer(DominitionChargeTimer, this, &AResourceCamp::ChargingComplete, 4.0f, false);
}

void AResourceCamp::RestorationProcess()
{
	GetWorldTimerManager().SetTimer(DominitionChargeTimer, this, &AResourceCamp::RestorationComplete, 4.0f, false);
}

void AResourceCamp::DominationProcess()
{
}

void AResourceCamp::PrintLogText_Implementation()
{

}
