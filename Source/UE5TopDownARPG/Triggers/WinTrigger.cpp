// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"
#include "../UE5TopDownARPGGameMode.h"

void AWinTrigger::Action(AActor* ActorInRange)
{
	AUE5TopDownARPGGameMode* GameMode = GetWorld()->GetAuthGameMode<AUE5TopDownARPGGameMode>();
	if (IsValid(GameMode))
	{
		GameMode->EndGame(true);
	}
}