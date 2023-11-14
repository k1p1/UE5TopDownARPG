// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"
#include "../UE5TopDownARPG.h"

void UBaseAbility::BeginDestroy()
{
	if (TimerManager)
	{
		TimerManager->ClearTimer(CooldownTimerHandle);
		TimerManager = nullptr;
	}
	Super::BeginDestroy();
}

bool UBaseAbility::Activate(FVector AimLocation)
{
	if (bIsOffCooldown == false)
	{
		return false;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("UAbility::Activate IsValid(World) == false"));
		return false;
	}

	TimerManager = &World->GetTimerManager();
	TimerManager->SetTimer(CooldownTimerHandle, this, &UBaseAbility::OnCooldownTimerEnded, CooldownTime);
	bIsOffCooldown = false;

	AActor* Owner = Cast<AActor>(GetOuter());
	if (IsValid(Owner) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("UAbility::Activate IsValid(Owner) == false"));
		return false;
	}

	return true;
}

void UBaseAbility::OnCooldownTimerEnded()
{
	bIsOffCooldown = true;
}

