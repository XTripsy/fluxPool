// Fill out your copyright notice in the Description page of Project Settings.


#include "Cores/FluxPoolSubsystem.h"

#include "Cores/FluxPoolableInterface.h"

void UFluxPoolSubsystem::InitializePoolComponentsServer(TArray<FFluxPoolComponents> items)
{
	UWorld* world = GetWorld();
	if (!world) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bDeferConstruction = false;
	
	for (const FFluxPoolComponents item : items)
	{
		FFluxPool& PoolData = PoolsServer.FindOrAdd(item.Identity);
		for (uint32 i = 0; i < item.Total; i++)
		{
			AActor* spawnedActor = world->SpawnActor<AActor>(
				item.Class,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
			if (!spawnedActor->Implements<UFluxPoolableInterface>()) continue;
			IFluxPoolableInterface::Execute_SetIdentity(spawnedActor, item.Identity);
			IFluxPoolableInterface::Execute_OnReturnToPool(spawnedActor);
			PoolData.Items.Add(spawnedActor);
		}
	}
}

void UFluxPoolSubsystem::InitializePoolComponentsClient(TArray<FFluxPoolComponents> items)
{
	UWorld* world = GetWorld();
	if (!world) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bDeferConstruction = false;
	
	for (const FFluxPoolComponents item : items)
	{
		FFluxPool& PoolData = PoolsClient.FindOrAdd(item.Identity);
		for (uint32 i = 0; i < item.Total; i++)
		{
			AActor* spawnedActor = world->SpawnActor<AActor>(
				item.Class,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
			if (!spawnedActor->Implements<UFluxPoolableInterface>()) continue;
			IFluxPoolableInterface::Execute_SetIdentity(spawnedActor, item.Identity);
			IFluxPoolableInterface::Execute_OnReturnToPool(spawnedActor);
			PoolData.Items.Add(spawnedActor);
		}
	}
}

TArray<AActor*> UFluxPoolSubsystem::PopObjectServer(FGameplayTag tag, int32 total)
{
	TArray<AActor*> result;
	if (!PoolsServer.Find(tag) || total == 0 || PoolsServer.Find(tag)->Items.IsEmpty()) return result;
	UObject* obj = nullptr;
	
	for (int32 i = 0; i < total; i++)
	{
		obj = PoolsServer.Find(tag)->Items.Pop().GetObject();
		if (!obj || !obj->Implements<UFluxPoolableInterface>()) continue;
		IFluxPoolableInterface::Execute_OnSpawnFromPool(obj);
		result.Add(Cast<AActor>(obj));
	}
	
	return result;
}

TArray<AActor*> UFluxPoolSubsystem::PopObjectClient(FGameplayTag tag, int32 total)
{
	TArray<AActor*> result;
	if (!PoolsClient.Find(tag) || total == 0 || PoolsClient.Find(tag)->Items.IsEmpty()) return result;
	UObject* obj = nullptr;
	
	for (int32 i = 0; i < total; i++)
	{
		obj = PoolsClient.Find(tag)->Items.Pop().GetObject();
		if (!obj || !obj->Implements<UFluxPoolableInterface>()) continue;
		IFluxPoolableInterface::Execute_OnSpawnFromPool(obj);
		result.Add(Cast<AActor>(obj));
	}
	
	return result;
}

void UFluxPoolSubsystem::PushObjectServer(FGameplayTag tag, UObject* object)
{
	if (!object || !object->Implements<UFluxPoolableInterface>()) return;
	
	FFluxPool& PoolData = PoolsServer.FindOrAdd(tag);
	PoolData.Items.Add(object);
	IFluxPoolableInterface::Execute_OnReturnToPool(object);
}

void UFluxPoolSubsystem::PushObjectClient(FGameplayTag tag, UObject* object)
{
	if (!object || !object->Implements<UFluxPoolableInterface>()) return;
	
	FFluxPool& PoolData = PoolsClient.FindOrAdd(tag);
	PoolData.Items.Add(object);
	IFluxPoolableInterface::Execute_OnReturnToPool(object);
}

void UFluxPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFluxPoolSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	PoolsServer.Empty();
	PoolsClient.Empty();
}
