// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FluxPoolActor.h"
#include "FluxPoolNiagara.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class FLUXPOOL_API AFluxPoolNiagara : public AFluxPoolActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Flux Component", meta = (DisplayPriority = "0"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Flux Niagara", meta = (DisplayPriority = "0"))
	TObjectPtr<UNiagaraSystem> NiagaraAssets;
	
private:
	UFUNCTION()
	void OnNiagaraFinish(UNiagaraComponent* Niagara);
	
public:
	AFluxPoolNiagara();
	virtual void PostInitProperties() override;
	virtual void OnSpawnFromPool_Implementation() override;
};
