// Fill out your copyright notice in the Description page of Project Settings.


#include "Templates/FluxPoolCharacter.h"

#include "Cores/FluxPoolSubsystem.h"


AFluxPoolCharacter::AFluxPoolCharacter()
{
	
}

void AFluxPoolCharacter::PostInitProperties()
{
	Super::PostInitProperties();
	PrimaryActorTick.bCanEverTick = IsUseTick;
	SetReplicates(IsReplicates);
}

void AFluxPoolCharacter::End()
{
	UFluxPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UFluxPoolSubsystem>();
	if (!Subsystem) return;
	Subsystem->PushObjectClient(Identity, this);
	if (!HasAuthority()) return;
	Subsystem->PushObjectServer(Identity, this);
}

void AFluxPoolCharacter::SetIdentity_Implementation(FGameplayTag tag)
{
	Identity = tag;
}

FGameplayTag AFluxPoolCharacter::GetIdentity_Implementation()
{
	return Identity;
}

void AFluxPoolCharacter::OnSpawnFromPool_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	
	OnSpawn();
}

void AFluxPoolCharacter::OnReturnToPool_Implementation()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	SetActorLocation(FVector(0.0f, 0.0f, -1000.0f));
	
	OnReturn();
}
