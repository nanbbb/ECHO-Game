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
			"ECHO/Variant_Horror",
			"ECHO/Variant_Horror/UI",
			"ECHO/Variant_Shooter",
			"ECHO/Variant_Shooter/AI",
			"ECHO/Variant_Shooter/UI",
			"ECHO/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
