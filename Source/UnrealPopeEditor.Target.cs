using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealPopeEditorTarget : TargetRules
{
    public UnrealPopeEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("UnrealPope");
    }
}
