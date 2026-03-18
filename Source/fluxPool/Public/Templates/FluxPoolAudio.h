// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FluxPoolActor.h"
#include "FluxPoolAudio.generated.h"

class UAudioComponent;
class USoundBase;

UCLASS()
class FLUXPOOL_API AFluxPoolAudio : public AFluxPoolActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Flux Component", meta = (DisplayPriority = "0"))
	TObjectPtr<UAudioComponent> AudioComponent;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Flux Audio", meta = (DisplayPriority = "0"))
	TObjectPtr<USoundBase> AudioAssets;
	
private:
	UFUNCTION()
	void OnSoundFinish();
	
public:
	AFluxPoolAudio();
	virtual void PostInitProperties() override;
	virtual void OnSpawnFromPool_Implementation() override;
};
