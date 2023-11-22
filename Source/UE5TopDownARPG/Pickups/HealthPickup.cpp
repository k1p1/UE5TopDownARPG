// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Engine/DamageEvents.h"
#include "../UE5TopDownARPGCharacter.h"

void AHealthPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
  Character->TakeDamage(-FMath::Abs(HealthPoints), FDamageEvent(UDamageType::StaticClass()), nullptr, this);
}