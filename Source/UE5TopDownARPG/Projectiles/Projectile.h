// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

};
