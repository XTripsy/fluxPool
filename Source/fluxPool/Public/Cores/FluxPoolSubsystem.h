// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Cores/FluxPoolStruct.h"
#include "FluxPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FLUXPOOL_API UFluxPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<FGameplayTag, FFluxPool> PoolsServer;
	
	UPROPERTY()
	TMap<FGameplayTag, FFluxPool> PoolsClient;
	
public:
	UFUNCTION(Category = "FluxPool")
	void InitializePoolComponentsServer(TArray<FFluxPoolComponents> items);
	
	UFUNCTION(Category = "FluxPool")
	void InitializePoolComponentsClient(TArray<FFluxPoolComponents> items);
	
	UFUNCTION(BlueprintCallable, Category = "FluxPool")
	TArray<AActor*> PopObjectServer(FGameplayTag tag, int32 total);
	
	UFUNCTION(Category = "FluxPool")
	TArray<AActor*> PopObjectClient(FGameplayTag tag, int32 total);
	
	UFUNCTION(BlueprintCallable, Category = "FluxPool")
	void PushObjectServer(FGameplayTag tag, UObject* object);
	
	UFUNCTION(Category = "FluxPool")
	void PushObjectClient(FGameplayTag tag, UObject* object);
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
