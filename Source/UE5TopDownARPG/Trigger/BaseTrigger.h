// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrigger.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API ABaseTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Action(AActor* ActorInRange);

	void CustomTick();

	UPROPERTY()
	AActor* Target;

	UPROPERTY(EditDefaultsOnly)
	float Range = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float CustomTickRate = 1.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
