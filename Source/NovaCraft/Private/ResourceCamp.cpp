// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCamp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
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




	GaegeBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaegeBar"));
	
	ConstructorHelpers::FClassFinder<UUserWidget>GaegeWidget(TEXT("WidgetBlueprint'/Game/00_Work/Common/Widget/CommonObject/WB_Gaege'"));

	if (GaegeWidget.Succeeded())
	{
		GaegeBar->SetupAttachment(RootComponent);
		GaegeBar->SetWidgetClass(GaegeWidget.Class);
		GaegeBar->SetDrawSize(FVector2D(200, 20));
		GaegeBar->SetWidgetSpace(EWidgetSpace::Screen);
	}
	


	this->OnTotalCountChanged.AddDynamic(this, &AResourceCamp::CheckCompetition);
	this->OnCampStateChganged.AddDynamic(this, &AResourceCamp::CampProcess);
}

// Called when the game starts or when spawned
void AResourceCamp::BeginPlay()
{
	Super::BeginPlay();
	
	static FString MI_Path = "/Game/SciFi_ReactorHangar/Materials/M_TNR2/ImpulsePlasma/ImpulsePlasma_mat_Inst";
	UMaterialInstance* MI_TeamColor = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInterface::StaticClass(), this, *MI_Path));

	if (MI_TeamColor != nullptr)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MI_TeamColor, this);

		if (DynamicMaterial)
		{
			CampBodyMesh->SetMaterial(20, DynamicMaterial);

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
	DOREPLIFETIME(AResourceCamp, DominitionChargeTimer);
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

			// Call CheckCompetition
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

			// Call CheckCompetition
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
	// 점령 시도 중인 유닛이 있다면
	if (ChangedTotalCount > 0)
	{
		// 경쟁 상태인지 확인해야함

		// 점령 중인 팀이 하나라면
		if (CheckTeamCount() == 1)
		{
			if (GetCampState() == E_CampState::Neutrality || GetCampState() == E_CampState::Competition)
			{
				// 점령 시작
				SetCampState(E_CampState::Charging);

				// Call CampProcess
				OnCampStateChganged.Broadcast(this->CampState);
			}
			else if (GetCampState() == E_CampState::Domination)
			{

				// 다른 팀이 점령한 상태라면
				if (DominationTeamNumber != GetDominationTeamIndex())
				{
					// 수복 시작
					SetCampState(E_CampState::Restoration);

					// Call CampProcess
					OnCampStateChganged.Broadcast(this->CampState);
				}
			}

		}
		else if (CheckTeamCount() >= 2) // 2팀 이상이 점령 중이라면
		{
			// 점령 상태 중단, 경쟁 상태 돌입
			SetCampState(E_CampState::Competition);

			// Call CampProcess
			OnCampStateChganged.Broadcast(this->CampState);
		}
	}
	else // 점령 시도 중인 유닛이 없다면
	{
		if (GetCampState() == E_CampState::Charging)
		{
			// 점령 중단 및 초기화
			SetCampState(E_CampState::Neutrality);
		
			// Call CampProcess
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
	switch (NewCampState)
	{
	case E_CampState::None:
		break;
	case E_CampState::Neutrality:
		NeutralityProcess();
		break;
	case E_CampState::Competition:
		CompetitionProcess();
		break;
	case E_CampState::Charging:
		ChargingProcess();
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

void AResourceCamp::ChargingProcess()
{

	if (GetWorldTimerManager().IsTimerPaused(DominitionChargeTimer))
	{
		GetWorldTimerManager().UnPauseTimer(DominitionChargeTimer);
	}
	else {

		GetWorldTimerManager().SetTimer(DominitionChargeTimer, this, &AResourceCamp::ChargingComplete, 4.0f, false);
	}
}

void AResourceCamp::ChargingComplete()
{
	SetCampState(E_CampState::Domination);
	GetWorldTimerManager().ClearTimer(DominitionChargeTimer);

	// Call CampProcess
	OnCampStateChganged.Broadcast(this->CampState);

}

void AResourceCamp::NeutralityProcess()
{
	GetWorldTimerManager().ClearTimer(DominitionChargeTimer);
}

void AResourceCamp::CompetitionProcess()
{
	if (GetWorldTimerManager().IsTimerActive(DominitionChargeTimer))
	{
		GetWorldTimerManager().PauseTimer(DominitionChargeTimer);
	}
}

void AResourceCamp::RestorationComplete()
{
	SetTeamColor(FLinearColor::Black);
	GetWorldTimerManager().ClearTimer(DominitionChargeTimer);

	PreDominationTeamNumber = GetDominationTeamNumber();
	SetDominationTeamNumber(-1);

	RestorationCamp();

	SetCampState(E_CampState::Charging);

	// Call CampProcess
	OnCampStateChganged.Broadcast(this->CampState);

}

void AResourceCamp::RestorationProcess()
{
	GetWorldTimerManager().ClearTimer(DominitionChargeTimer);
	GetWorldTimerManager().SetTimer(DominitionChargeTimer, this, &AResourceCamp::RestorationComplete, 4.0f, false);
}

void AResourceCamp::RestorationCamp_Implementation()
{
}

void AResourceCamp::DominationProcess()
{
	if (GetDominationTeamIndex() >= 0)
	{
		if (GetDominationTeamNumber() != -1)
		{
			PreDominationTeamNumber = GetDominationTeamNumber();
		}
		

		SetTeamColor(PlayerTeamColor[GetDominationTeamIndex()]);
		SetDominationTeamNumber(GetDominationTeamIndex());


		DominationComplete();

	}
}


FLinearColor AResourceCamp::GetTeamColorForGaege()
{
	switch (CampState)
	{
	case E_CampState::None:
		return FColor::Black;
		break;
	case E_CampState::Neutrality:
		return FColor::Black;
		break;
	case E_CampState::Competition:
		return this->PlayerTeamColor[GetDominationTeamIndex()];
		break;
	case E_CampState::Charging:
		return this->PlayerTeamColor[GetDominationTeamIndex()];
		break;
	case E_CampState::Restoration:

		if (GetDominationTeamIndex() == 0)
		{
			return this->PlayerTeamColor[1];
		}
		else {
			return this->PlayerTeamColor[0];
		}

		
		break;
	case E_CampState::Domination:
		return this->PlayerTeamColor[GetDominationTeamIndex()];
		break;
	default:
		return FColor::Black;
		break;
	}
}




void AResourceCamp::DominationComplete_Implementation()
{
}

void AResourceCamp::PrintLogText_Implementation()
{

}
