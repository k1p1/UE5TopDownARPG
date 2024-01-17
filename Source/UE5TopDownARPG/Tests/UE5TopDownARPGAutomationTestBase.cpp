#include "UE5TopDownARPGAutomationTestBase.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPG.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UWorld* FUE5TopDownARPGAutomationTestBase::GetAutomationTestWorld()
{
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts)
	{
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Game))
			&& (Context.World() != nullptr))
		{
			return Context.World();
		}
	}

	return nullptr;
}

TArray<AUE5TopDownARPGCharacter*> FUE5TopDownARPGAutomationTestBase::GetSpawnedCharacters(UWorld* World)
{
	TArray<AActor*> AllActors;
	TArray<AUE5TopDownARPGCharacter*> Result;
	UGameplayStatics::GetAllActorsOfClass(World, AUE5TopDownARPGCharacter::StaticClass(), AllActors);
	for (AActor* Actor : AllActors)
	{
		AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(Actor);
		if (IsValid(Character) && IsValid(Character->GetController()) == false)
		{
			Result.Add(Character);
		}
	}
	
	return Result;
}

bool FUE5TopDownARPGAutomationTestBase::SpawnCharacters(UWorld* World, TArray<TSubclassOf<AUE5TopDownARPGCharacter>> PlayableCharactersClasses)
{
	if (IsValid(World) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FUE5TopDownARPGAutomationTestBase::SpawnCharacters IsValid(World) == false"));
		return false;
	}

	if (PlayableCharactersClasses.Num() <= 0)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FUE5TopDownARPGAutomationTestBase::SpawnCharacters PlayableCharactersClass.Num() <= 0"));
		return false;
	}

	TArray<AActor*>	PlayerStartActors;
	TArray<APlayerStart*> PlayerStartPositions;

	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStartActors);
	PlayerStartPositions.SetNumZeroed(2);

	for (AActor* PlayerStartActor : PlayerStartActors)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
		if (PlayerStart->PlayerStartTag == "TestCharacter1")
		{
			PlayerStartPositions[0] = PlayerStart;
		}
		else if (PlayerStart->PlayerStartTag == "TestCharacter2")
		{
			PlayerStartPositions[1] = PlayerStart;
		}
	}

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 0; i < PlayerStartPositions.Num(); i++)
	{
		AUE5TopDownARPGCharacter* Character = World->SpawnActor<AUE5TopDownARPGCharacter>(PlayableCharactersClasses[i], PlayerStartPositions[i]->GetActorTransform(), ActorSpawnParameters);
	}

	return true;
}

