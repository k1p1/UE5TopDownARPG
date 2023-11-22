// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTrigger.h"

ASpawnTrigger::ASpawnTrigger()
{
  SpawnActorLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnActorLocationComponent"));
  SpawnActorLocationComponent->SetupAttachment(RootComponent);
}

void ASpawnTrigger::ActionStart(AActor* ActorInRange)
{
  Super::ActionStart(ActorInRange);

  if (GetWorld()->GetTimerManager().IsTimerActive(BetweenWavesTimerHandle) == false)
  {
    CurrentWave = 1;
    GetWorld()->GetTimerManager().SetTimer(BetweenWavesTimerHandle, this, &ASpawnTrigger::SpawnWave, DelayBetweenWaves, true, InitialDelay);
  }

}

void ASpawnTrigger::SpawnWave()
{
  FActorSpawnParameters SpawnParameters;
  SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

  for (int i = 0; i < NumberOfActorsPerWave; i++)
  {
    AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnActorLocationComponent->GetComponentLocation(), FRotator(), SpawnParameters);
  }

  if (CurrentWave == NumberOfWaves)
  {
    GetWorld()->GetTimerManager().ClearTimer(BetweenWavesTimerHandle);
  }
  else
  {
    CurrentWave++;
  }
}