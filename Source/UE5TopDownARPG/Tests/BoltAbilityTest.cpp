#include "BoltAbilityTest.h"
#include "UE5TopDownARPGAutomationTestBase.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"

#include "GameFramework/PlayerStart.h"

bool FLatent_ActivateAbility::Update()
{
	if (IsValid(ActiveCharacter) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FLatent_ActivateAbility::Update IsValid(ActiveCharacter) == false"));
		return false;
	}

	if (IsValid(TargetCharacter) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FLatent_ActivateAbility::Update IsValid(TargetCharacter) == false"));
		return false;
	}

	if (ActiveCharacter->ActivateAbility(TargetCharacter->GetActorLocation()) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FLatent_ActivateAbility::Update ActiveCharacter->ActivateAbility(TargetCharacter->GetActorLocation()) == false"));
		return false;
	}

	return true;
}

bool FLatent_CheckBoltAbilityTargetHealth::Update()
{
	UE_LOG(LogUE5TopDownARPG, Display, TEXT("Bolt skill - the target is expected to be at %f health"), ExpectedHealth);
	UE_LOG(LogUE5TopDownARPG, Display, TEXT("Target current health: %f"), Target->GetHealth());

	if (Target->GetHealth() != ExpectedHealth)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FTBoltAbilityTest::FLatent_CheckBoltTargetHealth() Target->GetHealth() != ExpectedHealth"));
	}
	else
	{
		UE_LOG(LogUE5TopDownARPG, Display, TEXT("Test Success ----- FTBoltAbilityTest::FLatent_CheckBoltTargetHealth() Target->GetHealth() == ExpectedHealth -----"));
	}
	
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FTBoltAbilityTest, FUE5TopDownARPGAutomationTestBase, "UE5TopDownARPG.BoltAbility",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ClientContext |
	EAutomationTestFlags::ProductFilter)

	bool FTBoltAbilityTest::RunTest(const FString& params)
{	
	AutomationOpenMap(TEXT("/Game/Content/TopDown/Maps/TopDownMap"));

	UWorld* World = GetAutomationTestWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FTBoltAbilityTest::RunTest() IsValid(World) == false"));
		return false;
	}

	FActorSpawnParameters ActorSpawnParameters;
	TArray<TSubclassOf<AUE5TopDownARPGCharacter>> PlayableCharactersClasses;

	TSoftClassPtr<AActor> ActorBpClass = TSoftClassPtr<AActor>(FSoftObjectPath(TEXT("Blueprint'/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C'")));
	UClass* LoadedBpAsset = ActorBpClass.LoadSynchronous();
	PlayableCharactersClasses.Add(LoadedBpAsset);
	PlayableCharactersClasses.Add(LoadedBpAsset);	

	if (SpawnCharacters(World, PlayableCharactersClasses) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FTBoltAbilityTest::RunTest() SpawnAndInitCharacters() returned false"));
		return false;
	}
	
	TArray<AUE5TopDownARPGCharacter*> SpawnedCharacters = GetSpawnedCharacters(World);
	AUE5TopDownARPGCharacter* ActiveCharacter = SpawnedCharacters[0];
	if (IsValid(ActiveCharacter) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FTBoltAbilityTest::RunTest() IsValid(ActiveCharacter) == false"));
		return false;
	}
	
	AUE5TopDownARPGCharacter* TargetCharacter = SpawnedCharacters[1];
	float StartingHealth = TargetCharacter->GetHealth();

	if (IsValid(TargetCharacter) == false)
	{
		UE_LOG(LogUE5TopDownARPG, Error, TEXT("FTBoltAbilityTest::RunTest() IsValid(TargetCharacter) == false"));
		return false;
	}
	
	float ExpectedHealth = StartingHealth - 50;

	ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(3.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FLatent_ActivateAbility(ActiveCharacter, TargetCharacter));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(3.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FLatent_CheckBoltAbilityTargetHealth(TargetCharacter, TargetCharacter->GetHealth(), ExpectedHealth));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(3.0f));
	
	ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand);

	return true;
}