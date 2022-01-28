// © 2022 Mohammad Jamal Sarvarian No rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class fourteen_weeksTarget : TargetRules
{
	public fourteen_weeksTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "fourteen_weeks" } );
	}
}
