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

	//// ������ ����
	//��Ȱ��ȭ�� ����, ���� ���� �ǹ�

	//// ���� ����
	//������ ������ ����, �ǹ� �� ����

	//// ���� ����
	//- ���� ���ָ� ���� ���
	//	- ����� ���� �������� ����� �ڽ��� ���� �������� ä���
	//- ���� �ٸ� ������ ���� ���
	//	- ���� ���� ������ ���¿��� ����
	//- ��� ������ ��� ��, ��� �������� �ʱ�ȭ �ȴ�.



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
