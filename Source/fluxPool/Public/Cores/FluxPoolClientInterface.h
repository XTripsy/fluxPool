// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "FluxPoolClientInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFluxPoolClientInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FLUXPOOL_API IFluxPoolClientInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Flux Pool Client")
	void PopObjectClients(FGameplayTag tag, FVector location, FRotator rotation);
};
