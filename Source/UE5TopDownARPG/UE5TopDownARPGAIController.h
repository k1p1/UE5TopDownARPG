// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UE5TopDownARPGAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AUE5TopDownARPGAIController : public AAIController
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGAIController();

private:
	virtual void OnPossess(class APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY()
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorComp;
};
