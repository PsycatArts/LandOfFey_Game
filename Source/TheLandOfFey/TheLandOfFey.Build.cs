// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheLandOfFey : ModuleRules
{
	public TheLandOfFey(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HeadMountedDisplay",  "StateMachine",  "NavigationSystem" , "ElementalAbilitySystem", "AkAudio", "WwiseSoundEngine"/*, "CameraShake"*/ });
	}
}
