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
	TSubclassOf<class AActor> SpawnActorClass;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SpawnActorLocationComponent;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfWaves;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfActorsPerWave;

	UPROPERTY(EditDefaultsOnly)
	float InitialDelay;

	UPROPERTY(EditDefaultsOnly)
	float DelayBetweenWaves;

	FTimerHandle BetweenWavesTimerHandle;

private:
	void SpawnWave();

	int CurrentWave;
};
