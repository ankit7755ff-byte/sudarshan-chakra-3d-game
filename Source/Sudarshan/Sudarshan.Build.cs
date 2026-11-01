using UnrealBuildTool;

public class Sudarshan : ModuleRules
{
	public Sudarshan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Niagara",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  
			"Slate", 
			"SlateCore" 
		});
	}
}
