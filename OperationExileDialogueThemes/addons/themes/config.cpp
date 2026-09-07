class CfgPatches
{
    class OperationExileDialogueThemes
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DialogueFramework"};
    };
};

class CfgMods
{
    class OperationExileDialogueThemes
    {
        dir = "OperationExileDialogueThemes";
        name = "Operation Exile Dialogue Themes";
        author = "CtrlQuest";
        credits = "Dialogue Framework by ABTT ESK";
        version = "0.3.1";
        type = "mod";
        dependencies[] = {"Mission"};
        class defs
        {
            class missionScriptModule
            {
                value = "";
                files[] = {"operationexiledialoguethemes/addons/themes/Scripts/5_Mission"};
            };
        };
    };
};

// Exact NPC AND tree pairs for quest contacts; real market context for traders.
// These visual assignments never change NPC factions, quests or trader stock.
// This file is packed with the client addon. It is NOT a server-profile JSON.
class CfgOperationExileDialogueThemes
{
    class UCF
    {
        enabled = 1;
        npcID = 5;
        treeID = 5;
        code = "UCF";
        fullName = "UNITED COALITION FORCES";
        frameTexture = "operationexiledialoguethemes/addons/themes/GUI/textures/ucf_frame_ca.paa";
        label = "COALITION LIAISON";
        subtitle = "OPERATION EXILE / FIELD LIAISON";
        // Display tint counters the much brighter in-game texture rendering.
        // Alpha stays fully opaque here; the PAA's cut-out alpha is preserved.
        FrameTintColor[] = {255, 58, 56, 64};
        BrandColor[] = {255, 199, 194, 172};
        BackgroundColor[] = {255, 12, 13, 10};
        ResponseBackgroundColor[] = {255, 15, 16, 12};
        HoverBorderColor[] = {255, 199, 145, 40};
        SpeakerNameColor[] = {255, 142, 153, 86};
        SpeakerTextColor[] = {255, 229, 226, 213};
        ResponseTextColor[] = {255, 229, 226, 213};
        RewardSelectedColor[] = {255, 40, 42, 25};
        WindowBorderColor[] = {255, 58, 60, 43};
        HeaderColor[] = {255, 13, 14, 11};
        AccentColor[] = {255, 109, 116, 68};
    };
    class CCA
    {
        enabled = 1;
        npcID = 4;
        treeID = 4;
        code = "CCA";
        fullName = "CHERNARUS COMPLIANCE AUTHORITY";
        frameTexture = "operationexiledialoguethemes/addons/themes/GUI/textures/cca_frame_ca.paa";
        label = "SANCTUARY CONTACT";
        subtitle = "OPERATION EXILE / LOCAL CONTACT";
        BackgroundColor[] = {248, 20, 18, 16};
        ResponseBackgroundColor[] = {242, 33, 28, 23};
        HoverBorderColor[] = {255, 220, 160, 76};
        SpeakerNameColor[] = {255, 221, 198, 163};
        SpeakerTextColor[] = {255, 235, 221, 197};
        ResponseTextColor[] = {255, 228, 211, 185};
        RewardSelectedColor[] = {245, 93, 59, 33};
        WindowBorderColor[] = {255, 115, 91, 66};
        HeaderColor[] = {255, 69, 33, 25};
        AccentColor[] = {255, 185, 105, 76};
    };
    class GreenMountain
    {
        enabled = 1;
        // Lower this header inside the radio frame, not over its upper rim.
        HeaderOffsetY = 0.04;
        npcID = 1;
        treeID = 1;
        testNpcID = 6;
        testTreeID = 6;
        code = "GM";
        fullName = "GREEN MOUNTAIN RADIO";
        frameTexture = "operationexiledialoguethemes/addons/themes/GUI/textures/gm_frame_ca.paa";
        label = "SURVIVOR CONTRACTS";
        subtitle = "OPERATION EXILE / GREEN MOUNTAIN";
        BackgroundColor[] = {248, 13, 24, 26};
        ResponseBackgroundColor[] = {242, 20, 37, 40};
        HoverBorderColor[] = {255, 218, 181, 107};
        SpeakerNameColor[] = {255, 188, 216, 209};
        SpeakerTextColor[] = {255, 236, 232, 216};
        ResponseTextColor[] = {255, 220, 230, 222};
        RewardSelectedColor[] = {245, 49, 80, 79};
        WindowBorderColor[] = {255, 92, 120, 119};
        HeaderColor[] = {255, 21, 43, 49};
        AccentColor[] = {255, 176, 189, 166};
    };
    class Traders
    {
        enabled = 1;
        allTraders = 1;
        code = "EX";
        fullName = "INDEPENDENT TRADE NETWORK";
        frameTexture = "operationexiledialoguethemes/addons/themes/GUI/textures/trader_frame_ca.paa";
        label = "TRADE COUNTER";
        subtitle = "OPERATION EXILE / GOODS AND SERVICES";
        BackgroundColor[] = {248, 22, 23, 25};
        ResponseBackgroundColor[] = {242, 31, 32, 33};
        HoverBorderColor[] = {255, 220, 183, 102};
        SpeakerNameColor[] = {255, 218, 197, 153};
        SpeakerTextColor[] = {255, 236, 233, 224};
        ResponseTextColor[] = {255, 225, 225, 216};
        RewardSelectedColor[] = {245, 83, 72, 45};
        WindowBorderColor[] = {255, 118, 106, 77};
        HeaderColor[] = {255, 30, 32, 34};
        AccentColor[] = {255, 186, 161, 109};
    };
};
