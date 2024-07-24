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
			//for���� ���鼭 Ǯ���ҹ�ü�� �����Ͽ� Ǯ�������Ѿ��ͺ����� ����
			//���� Ǯ�������Ѿ��͸� ��Ȱ��ȭ�ϰ� �ε����� ���ʴ�� ����, ��Ǯ�������Ʈ�����Լ� ���ε�(?), ������ƮǮ�迭�� Ǯ�������� ���� �߰�
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
	//objectpool �迭�� for������ �����鼭 Ǯ�������Ѿ��Ͱ� ��������ʰ� ��Ȱ��ȭ�Ȼ��¶��
	//Ǯ�������� ���͸� �ڷ���Ʈ��Ű�� �����ֱ⸦ �����ϰ� Ȱ��ȭ��Ŵ �׷����� ������Ǯ�ε����迭�� �����Ǿ��� �ε����� �߰�
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




