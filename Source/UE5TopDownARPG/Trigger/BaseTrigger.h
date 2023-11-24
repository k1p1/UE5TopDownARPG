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

	virtual void ActionStart(AActor* ActorInRange);
	virtual void ActionEnd(AActor* ActorInRange);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
