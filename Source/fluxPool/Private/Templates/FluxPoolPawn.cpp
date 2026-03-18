// Fill out your copyright notice in the Description page of Project Settings.


#include "Templates/FluxPoolPawn.h"

#include "Cores/FluxPoolSubsystem.h"

AFluxPoolPawn::AFluxPoolPawn()
{
	
}

void AFluxPoolPawn::PostInitProperties()
{
	Super::PostInitProperties();
	PrimaryActorTick.bCanEverTick = IsUseTick;
	SetReplicates(IsReplicates);
}

void AFluxPoolPawn::End()
{
	UFluxPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UFluxPoolSubsystem>();
	if (!Subsystem) return;
	Subsystem->PushObjectClient(Identity, this);
	if (!HasAuthority()) return;
	Subsystem->PushObjectServer(Identity, this);
}

void AFluxPoolPawn::SetIdentity_Implementation(FGameplayTag tag)
{
	Identity = tag;
}

FGameplayTag AFluxPoolPawn::GetIdentity_Implementation()
{
	return Identity;
}

void AFluxPoolPawn::OnSpawnFromPool_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AFluxPoolPawn::OnReturnToPool_Implementation()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetActorLocation(FVector(0.0f, 0.0f, -1000.0f));
}
