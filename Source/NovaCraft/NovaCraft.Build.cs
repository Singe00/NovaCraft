// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NovaCraft : ModuleRules
{
	public NovaCraft(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "UMG" ,"EnhancedInput","OnlineSubsystem","OnlineSubsystemSteam" });
    }
}
