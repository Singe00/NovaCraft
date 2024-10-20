// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnpooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class NOVACRAFT_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	FOnpooledObjectDespawn OnPooledObjectDespawn;

	UFUNCTION(BlueprintCallable, Category="Pooled Object")
		void Deactivate();

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void SetTargetActor(AActor* actor);
	
	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
		void SetHomingTarget(AActor* target);

	bool IsActive();
	int GetPoolIndex();

	UPROPERTY(BlueprintReadOnly)
		AActor* TargetActor;
	UPROPERTY(BlueprintReadOnly)
		float ProjectileDamage;
	
	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UBoxComponent* BoxCollision;


	/*void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	bool isOverlap;*/

protected:
	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;
	
	

	FTimerHandle LifeSpanTimer;

};
