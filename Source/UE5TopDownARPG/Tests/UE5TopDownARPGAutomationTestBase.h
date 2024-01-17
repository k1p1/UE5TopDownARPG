#pragma once

#include "CoreMinimal.h"

#include "Misc/AutomationTest.h"
//#include "Tests/AutomationCommon.h"

class UE5TOPDOWNARPG_API FUE5TopDownARPGAutomationTestBase : public FAutomationTestBase
{
public:

	FUE5TopDownARPGAutomationTestBase(const FString& InName, const bool bInComplexTask)
		: FAutomationTestBase(InName, bInComplexTask)
	{
	}

	class UWorld* GetAutomationTestWorld();
	TArray<class AUE5TopDownARPGCharacter*> GetSpawnedCharacters(class UWorld* World);
	static bool SpawnCharacters(class UWorld* World, TArray<TSubclassOf<class AUE5TopDownARPGCharacter>> PlayableCharactersClasses);
};