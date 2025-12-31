// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ECHO : ModuleRules
{
	public ECHO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"AudioMixer",
			"AudioExtensions"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ECHO",
			"ECHO/Actors",
			"ECHO/Characters",
			"ECHO/System"
		});
	}
}
