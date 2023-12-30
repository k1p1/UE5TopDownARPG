// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5TopDownARPG : ModuleRules
{
	public UE5TopDownARPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTasks" });
    }
}
