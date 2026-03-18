// Fill out your copyright notice in the Description page of Project Settings.


#include "Templates/FluxPoolActor.h"

#include "Cores/FluxPoolSubsystem.h"


AFluxPoolActor::AFluxPoolActor()
{
	
}

void AFluxPoolActor::PostInitProperties()
{
	Super::PostInitProperties();
	PrimaryActorTick.bCanEverTick = IsUseTick;
	SetReplicates(IsReplicates);
}

void AFluxPoolActor::End()
{
	UFluxPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UFluxPoolSubsystem>();
	if (!Subsystem) return;
	Subsystem->PushObjectClient(Identity, this);
	if (!HasAuthority()) return;
	Subsystem->PushObjectServer(Identity, this);
}

void AFluxPoolActor::SetIdentity_Implementation(FGameplayTag tag)
{
	Identity = tag;
}

FGameplayTag AFluxPoolActor::GetIdentity_Implementation()
{
	return Identity;
}

void AFluxPoolActor::OnSpawnFromPool_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AFluxPoolActor::OnReturnToPool_Implementation()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetActorLocation(FVector(0.0f, 0.0f, -1000.0f));
}
