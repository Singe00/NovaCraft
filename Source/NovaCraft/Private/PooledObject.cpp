// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"



// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!BoxCollision)
	{
		// Use a box as a simple collision representation.
		BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
		// Set the box's collision size.
		BoxCollision->SetBoxExtent(FVector(32.0f, 10.0f, 10.0f));
		// Set the root component to be the collision component.
		RootComponent = BoxCollision;
	}


	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->InitialSpeed = 0.0f;
		ProjectileMovementComponent->MaxSpeed = 0.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		ProjectileMovementComponent->HomingAccelerationMagnitude = 1000.0f;

	}
	//BoxCollision->OnComponentHit.AddDynamic(this, &APooledObject::OnHit);
}

// Called when the game starts or when spawned
void APooledObject::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void APooledObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledObject::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

void APooledObject::SetActive(bool IsActive)
{
	Active = IsActive;
	SetActorHiddenInGame(!IsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, LifeSpan, false);
}

void APooledObject::SetLifeSpan(float LifeTime)
{
	LifeSpan = LifeTime;
}

void APooledObject::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

void APooledObject::SetTargetActor(AActor* actor)
{
	TargetActor = actor;
}

void APooledObject::SetDamage(float damage)
{
	ProjectileDamage = damage;
}

void APooledObject::SetHomingTarget(AActor* target)
{
	
	ProjectileMovementComponent->HomingTargetComponent = target->GetRootComponent();
	ProjectileMovementComponent->bIsHomingProjectile = true;
}

bool APooledObject::IsActive()
{
	return Active;
}

int APooledObject::GetPoolIndex()
{
	return PoolIndex;
}

void APooledObject::onHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}



