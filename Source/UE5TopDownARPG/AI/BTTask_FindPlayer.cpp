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

  APawn* PossesedPawn = AIController->GetPawn();
  if (IsValid(PossesedPawn) == false)
  {
    return EBTNodeResult::Failed;
  }

  UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
  if (IsValid(NavSys) == false)
  {
    return EBTNodeResult::Failed;
  }

  TArray<AActor*> FoundActors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUE5TopDownARPGCharacter::StaticClass(), FoundActors);

  for (AActor* Actor : FoundActors)
  {
    AUE5TopDownARPGCharacter* UE5TopDownARPGCharacter = Cast<AUE5TopDownARPGCharacter>(Actor);
    if (IsValid(UE5TopDownARPGCharacter) == false)
    {
      continue;
    }

    APlayerController* PlayerController = Cast<APlayerController>(UE5TopDownARPGCharacter->GetController());
    if (IsValid(PlayerController) == false)
    {
      continue;
    }

    UNavigationPath* Path = NavSys->FindPathToLocationSynchronously(GetWorld(), PossesedPawn->GetActorLocation(), Actor->GetActorLocation());
    if (Path->IsValid() && Path->IsPartial() == false)
    {
      UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
      if (IsValid(BlackboardComponent) == false)
      {
        return EBTNodeResult::Failed;
      }

      BlackboardComponent->SetValueAsObject(FName("Target"), Actor);
      return EBTNodeResult::Succeeded;
    }
  }
  return EBTNodeResult::Failed;
}