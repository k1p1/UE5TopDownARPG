// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "Engine/DamageEvents.h"

void AHealthPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
  Character->TakeDamage(-HealAmount, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
}

