// Fill out your copyright notice in the Description page of Project Settings.


#include "Templates/FluxPoolNiagara.h"

#include "NiagaraComponent.h"

void AFluxPoolNiagara::OnNiagaraFinish(UNiagaraComponent* Niagara)
{
	NiagaraComponent->Deactivate();
	End();
}

AFluxPoolNiagara::AFluxPoolNiagara()
{
	IsUseTick = false;
	IsReplicates = false;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &AFluxPoolNiagara::OnNiagaraFinish);
	NiagaraComponent->bAutoActivate = false;
	NiagaraComponent->Deactivate();
}

void AFluxPoolNiagara::PostInitProperties()
{
	Super::PostInitProperties();
	NiagaraComponent->SetAsset(NiagaraAssets);
}

void AFluxPoolNiagara::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
	if (!NiagaraComponent->GetAsset()) return;
	NiagaraComponent->Activate(true);
}
