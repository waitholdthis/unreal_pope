using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealPopeTarget : TargetRules
{
    public UnrealPopeTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("UnrealPope");
    }
}
