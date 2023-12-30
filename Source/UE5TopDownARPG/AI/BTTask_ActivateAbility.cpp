// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivateAbility.h"
#include "../UE5TopDownARPGCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
  AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
  if (IsValid(AIController) == false)
  {
    return EBTNodeResult::Failed;
  }

  AUE5TopDownARPGCharacter* PossesedCharacter = Cast<AUE5TopDownARPGCharacter>(AIController->GetPawn());
  if (IsValid(PossesedCharacter) == false)
  {
    return EBTNodeResult::Failed;
  }

  UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
  if (IsValid(BlackboardComponent) == false)
  {
    return EBTNodeResult::Failed;
  }

  AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(FName("Target")));
  if (IsValid(Target) == false)
  {
    return EBTNodeResult::Failed;
  }

  if (PossesedCharacter->ActivateAbility(Target->GetActorLocation()) == false)
  {
    return EBTNodeResult::Failed;
  }

  return EBTNodeResult::Succeeded;
}