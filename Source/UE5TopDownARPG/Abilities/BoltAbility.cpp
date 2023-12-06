// Fill out your copyright notice in the Description page of Project Settings.


#include "BoltAbility.h"
#include "../Projectiles/Projectile.h"
#include "../Animations/UE5TopDownARPGAnimInstance.h"

#include "GameFramework/Character.h"

bool UBoltAbility::Activate(FVector Location)
{
  if (Super::Activate(Location) == false)
  {
    return false;
  }

	ACharacter* Owner = Cast<ACharacter>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return false;
	}

	USkeletalMeshComponent* SkeletalMesh = Owner->GetMesh();
	if (IsValid(SkeletalMesh))
	{
		UUE5TopDownARPGAnimInstance* AnimInstance = Cast<UUE5TopDownARPGAnimInstance>(SkeletalMesh->GetAnimInstance());
		if (IsValid(AnimInstance))
		{
			AnimInstance->SetIsAttacking(true);
		}
	}

	FVector Direction = Location - Owner->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector ProjectileSpawnLocation = Owner->GetActorLocation() + Direction * 100.0f;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileSpawnLocation, Direction.Rotation(), SpawnParameters);
	if (IsValid(Projectile) == false)
	{
		return false;
	}

  return true;
}