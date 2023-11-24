// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"

ASpawnTrigger::ASpawnTrigger()
{
	SpawnLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocationComponent"));
	SpawnLocationComponent->SetupAttachment(RootComponent);
}

void ASpawnTrigger::ActionStart(AActor* ActorInRange)
{
	CurrentWave = 1;

	GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimerHandle, this, &ASpawnTrigger::SpawnWave, TimeBetweenWaves, true, InitialDelay);
}

void ASpawnTrigger::SpawnWave()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 0; i < NumberOfActorsToSpawn; i++)
	{
		GetWorld()->SpawnActor<AActor>(ActorToSpawnClass, SpawnLocationComponent->GetComponentLocation(), FRotator(), SpawnParameters);
	}

	if (CurrentWave == NumberOfWaves)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimerHandle);
		return;
	}

	CurrentWave++;
}