// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Wraith : ModuleRules
{
	public Wraith(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks",
			"ModularGameplay", "GameFeatures", "AIModule", "UMG", "SlateCore"
		});
	}
}