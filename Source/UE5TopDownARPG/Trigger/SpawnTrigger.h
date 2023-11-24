// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "SpawnTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ASpawnTrigger : public ABaseTrigger
{
	GENERATED_BODY()
public:
	ASpawnTrigger();

protected:
	virtual void ActionStart(AActor* ActorInRange) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawnClass;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SpawnLocationComponent;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfWaves = 1;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfActorsToSpawn = 1;

	UPROPERTY(EditDefaultsOnly)
	float InitialDelay;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenWaves = 1.0f;

	FTimerHandle WaveSpawnTimerHandle;
private:
	void SpawnWave();

	int CurrentWave;
};
