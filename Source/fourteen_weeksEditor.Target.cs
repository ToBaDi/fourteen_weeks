// © 2022 Mohammad Jamal Sarvarian No rights reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class fourteen_weeksEditorTarget : TargetRules
{
	public fourteen_weeksEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "fourteen_weeks" } );
	}
}
