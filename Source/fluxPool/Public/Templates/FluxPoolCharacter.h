// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cores/FluxPoolableInterface.h"
#include "GameFramework/Character.h"
#include "FluxPoolCharacter.generated.h"

UCLASS()
class FLUXPOOL_API AFluxPoolCharacter : public ACharacter, public IFluxPoolableInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "FluxPool", meta = (DisplayPriority = "0"))
	bool IsUseTick;
	
	UPROPERTY(EditAnywhere, Category = "FluxPool", meta = (DisplayPriority = "0"))
	bool IsReplicates;
	
	UPROPERTY(VisibleAnywhere, Category = "FluxPool", meta = (DisplayPriority = "0"))
	FGameplayTag Identity;
	
public:
	AFluxPoolCharacter();

protected:
	virtual void PostInitProperties() override;
	
	UFUNCTION(BlueprintCallable, Category = "FluxPool")
	void End();
	
public:
	virtual void SetIdentity_Implementation(FGameplayTag tag) override;
	virtual FGameplayTag GetIdentity_Implementation() override;
	virtual void OnSpawnFromPool_Implementation() override;
	virtual void OnReturnToPool_Implementation() override;
};
