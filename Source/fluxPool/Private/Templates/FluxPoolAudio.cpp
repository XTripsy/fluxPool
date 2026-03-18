// Fill out your copyright notice in the Description page of Project Settings.


#include "Templates/FluxPoolAudio.h"

#include "Components/AudioComponent.h"

void AFluxPoolAudio::OnSoundFinish()
{
	AudioComponent->Deactivate();
	End();
}

AFluxPoolAudio::AFluxPoolAudio()
{
	IsUseTick = false;
	IsReplicates = false;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->OnAudioFinished.AddDynamic(this, &AFluxPoolAudio::OnSoundFinish);
	AudioComponent->bAutoActivate = false;
	AudioComponent->Deactivate();
}

void AFluxPoolAudio::PostInitProperties()
{
	Super::PostInitProperties();
	AudioComponent->SetSound(AudioAssets);
}

void AFluxPoolAudio::OnSpawnFromPool_Implementation()
{
	Super::OnSpawnFromPool_Implementation();
	if (!AudioComponent->GetSound()) return;
	AudioComponent->Activate(true);
	AudioComponent->Play();
}
