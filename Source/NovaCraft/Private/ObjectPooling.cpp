// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPooling.h"

// Sets default values for this component's properties
UObjectPooling::UObjectPooling()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPooling::BeginPlay()
{
	Super::BeginPlay();

	if (PooledObjectSubclass != nullptr) 
	{
		UWorld* const World = GetWorld();
		
		if(World != nullptr)
		{
			//for문을 돌면서 풀링할물체를 스폰하여 풀링가능한액터변수로 정의
			//이후 풀링가능한액터를 비활성화하고 인덱스를 차례대로 배정, 온풀드오프젝트디스폰함수 바인딩(?), 오브젝트풀배열에 풀링가능한 액터 추가
			for (int i = 0; i < PoolSize; i++)
			{
				APooledObject* PoolableActor = World->SpawnActor<APooledObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);

				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPooling::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}

	}
	
}

APooledObject* UObjectPooling::SpawnPooledObject()
{
	//objectpool 배열을 for문으로 돌리면서 풀링가능한액터가 비어있지않고 비활성화된상태라면
	//풀링가능한 액터를 텔레포트시키고 생명주기를 세팅하고 활성화시킴 그런다음 스폰된풀인덱스배열에 지정되었던 인덱스로 추가
	for (APooledObject* PoolableActor : ObjectPool)
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			

			return PoolableActor;
		}
	}
	if (SpawnedPoolIndexes.Num() > 0) 
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		APooledObject* PoolableActor = ObjectPool[PooledObjectIndex];

		if (PoolableActor != nullptr)
		{
			PoolableActor->SetActive(false);

			PoolableActor->TeleportTo(FVector(0, 0, 0), FRotator(0, 0, 0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			

			return PoolableActor;
		}
	}

	return nullptr;
}


void UObjectPooling::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}




