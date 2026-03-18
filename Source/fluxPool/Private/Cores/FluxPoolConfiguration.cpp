// Fill out your copyright notice in the Description page of Project Settings.


#include "Cores/FluxPoolConfiguration.h"

#include "Cores/FluxPoolSubsystem.h"

AFluxPoolConfiguration::AFluxPoolConfiguration()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AFluxPoolConfiguration::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetActorLocation(FVector::ZeroVector);
}

void AFluxPoolConfiguration::BeginPlay()
{
	Super::BeginPlay();
	UFluxPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UFluxPoolSubsystem>();
	
	if (!Subsystem) return;
	Subsystem->InitializePoolComponentsClient(PoolItemsClient);
	
	if (!HasAuthority()) return;
	Subsystem->InitializePoolComponentsServer(PoolItemsServer);
}
