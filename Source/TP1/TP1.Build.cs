// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP1 : ModuleRules
{
	public TP1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"UMG", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemSteam", "Steamworks"});
		
	}
}
