// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceCamp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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


	DominationCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DominationZone"));
	DominationCollision->SetupAttachment(CampBodyMesh);


	DominationCollision->OnComponentBeginOverlap.AddDynamic(this, &AResourceCamp::OnComponentBeginOverlap);
	DominationCollision->OnComponentEndOverlap.AddDynamic(this, &AResourceCamp::OnComponentEndOverlap);
}

// Called when the game starts or when spawned
void AResourceCamp::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AResourceCamp::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnitBase* CompetitionUnit = Cast<AUnitBase>(OtherActor);

	if (CompetitionUnit)
	{
		CompetitionTeam[CompetitionUnit->TeamNumber] += 1;
		this->totalCount+=1;

		CompetitionUnit->OnUnitDead.AddDynamic(this, &AResourceCamp::DecreaseTeamCount);

	}
}

void AResourceCamp::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnitBase* CompetitionUnit = Cast<AUnitBase>(OtherActor);

	if (CompetitionUnit)
	{
		DecreaseTeamCount(CompetitionUnit);
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
		}
	}
}

void AResourceCamp::OnRep_Counting()
{
	PrintLogText();
}

void AResourceCamp::PrintLogText_Implementation()
{
}
