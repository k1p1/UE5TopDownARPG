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

	ServerRPC_SpawnProjectile(Location);

	return true;
}

void UBoltAbility::ServerRPC_SpawnProjectile_Implementation(FVector Location)
{
	ACharacter* Owner = Cast<ACharacter>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return;
	}

	USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
	if (IsValid(MeshComponent))
	{
		UUE5TopDownARPGAnimInstance* AnimInstance = Cast<UUE5TopDownARPGAnimInstance>(MeshComponent->GetAnimInstance());
		if (IsValid(AnimInstance))
		{
			AnimInstance->SetIsAttacking();
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
		return;
	}

	return;
}
