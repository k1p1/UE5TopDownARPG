// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"
#include "../UE5TopDownARPGCharacter.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "NavigationPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	if (IsValid(AIController) == false)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (IsValid(NavSys) == false)
	{
		return EBTNodeResult::Failed;
	}

	AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(AIController->GetPawn());
	if (IsValid(Character) == false)
	{
		return EBTNodeResult::Failed;
	}

	TArray<AActor*> FoundActors, PlayerActors;
	FVector RandomPt;
	FVector CharacterLocation = Character->GetActorLocation();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUE5TopDownARPGCharacter::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		UNavigationPath* Path = NavSys->FindPathToLocationSynchronously(GetWorld(), CharacterLocation, Actor->GetActorLocation());
		const bool IsPathToTargetValid = Path->IsValid() && Path->IsPartial() == false;
		if (IsPathToTargetValid)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), Actor);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
