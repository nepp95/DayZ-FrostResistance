class CfgPatches
{
    class FrostResistance
    {
        requiredAddons[] = {};
    };
};

class CfgMods
{
    class FrostResistance
    {
        type = "mod";

        class defs
        {
            class engineScriptModule
            {
                value = "";
                files[] = { "FrostResistance/1_Core" };
            };
            
            class gameScriptModule
            {
                value = "";
                files[] = { "FrostResistance/3_Game" };
            };

            class worldScriptModule
            {
                value = "";
                files[] = { "FrostResistance/4_World" };
            };

            class missionScriptModule
            {
                value = "";
                files[] = { "FrostResistance/5_Mission" };
            };
        };
    };
};