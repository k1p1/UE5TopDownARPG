// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"
#include "../UE5TopDownARPGGameMode.h"

void AWinTrigger::ActionStart(AActor* ActorInRange)
{
  AUE5TopDownARPGGameMode* GameMode = Cast<AUE5TopDownARPGGameMode>(GetWorld()->GetAuthGameMode());
  if (IsValid(GameMode))
  {
    GameMode->EndGame(true);
  }
}
