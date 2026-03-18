// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FluxPoolStruct.generated.h"

class IFluxPoolableInterface;

USTRUCT(BlueprintType)
struct FFluxPoolComponents
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UObject> Class;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Identity;
	
	UPROPERTY(EditAnywhere)
	uint32 Total;
};

USTRUCT(BlueprintType)
struct FFluxPool
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<TScriptInterface<IFluxPoolableInterface>> Items;
};
