// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorEnums.h"
#include "UnitBase.h"
#include "GameFramework/Actor.h"
#include "ResourceCamp.generated.h"

UCLASS()
class NOVACRAFT_API AResourceCamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceCamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CampBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* DominationCollision;

	//// 비점령 상태
	//비활성화된 비콘, 색이 꺼진 건물

	//// 점령 상태
	//점령자 색으로 비콘, 건물 색 설정

	//// 경합 상태
	//- 한쪽 유닛만 있을 경우
	//	- 상대의 점령 게이지를 지우고 자신의 점령 게이지를 채운다
	//- 팀이 다른 유닛이 있을 경우
	//	- 현재 점령 게이지 상태에서 중지
	//- 모든 유닛이 벗어날 시, 모든 게이지가 초기화 된다.



private:
	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	E_CampState CampState = E_CampState::Neutrality;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	int DominationTeamNumber = -1;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	bool IsCompetition = false;

	UPROPERTY(VisibleAnywhere, Category = "Manage|Value")
	TArray<int> CompetitionTeam = { 0,0,0,0 };

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Counting, Category = "Manage|Value")
	int totalCount = 0;

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

	UFUNCTION()
	void OnRep_Counting();


	//Getter
public:

	UFUNCTION(BlueprintCallable)
	int GetTotalCount() const { return this->totalCount; }
};
