// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Cores/FluxPoolStruct.h"
#include "FluxPoolConfiguration.generated.h"

UCLASS(NotBlueprintable, HideCategories=(Rendering, Replication, Collision, Input, 
		Actor, LOD, Cooking, Transform, Physics, Networking, LevelInstance))
class FLUXPOOL_API AFluxPoolConfiguration final : public AInfo
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Pool Configuration", meta = (DisplayPriority = "0"))
	TArray<FFluxPoolComponents> PoolItemsServer;
	
	UPROPERTY(EditAnywhere, Category = "Pool Configuration", meta = (DisplayPriority = "0"))
	TArray<FFluxPoolComponents> PoolItemsClient;
	
public:
	AFluxPoolConfiguration();
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
};
