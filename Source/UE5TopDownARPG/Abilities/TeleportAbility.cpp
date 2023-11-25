// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportAbility.h"
#include "../UE5TopDownARPG.h"

bool UTeleportAbility::Activate(FVector Location)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Executing teleportation"));

	if (Super::Activate(Location) == false)
	{
		return false;
	}

	AActor* Owner = Cast<AActor>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return false;
	}

	FVector TeleportationVector = Location - Owner->GetActorLocation();

	if (TeleportationVector.Size() > MaxRange)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("TeleportationRange exceedes the maximum range"));
		return false;
	}

	if (TeleportationVector.Size() < MinRange)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("TeleportationRange is less than the minimum range"));
		return false;
	}

	FVector OriginPosition = Owner->GetActorLocation();

	FVector NewPosition = Location;
	NewPosition.Z = NewPosition.Z + ZOffset;

	FHitResult* OutSweepHitResult = new FHitResult();

	bool TeleportationResult  = Owner->SetActorLocation(NewPosition, !CanTeleportOverObstacle, OutSweepHitResult);

	if (!CanTeleportOverObstacle && OutSweepHitResult->GetComponent()) {
		if (DoesRetract) {
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("The player was retracted"));
		}
		else
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("The player can not teleport over obstacles"));
			Owner->SetActorLocation(OriginPosition);
			TeleportationResult = false;
		}
	}

	delete OutSweepHitResult;

	return TeleportationResult;
}
