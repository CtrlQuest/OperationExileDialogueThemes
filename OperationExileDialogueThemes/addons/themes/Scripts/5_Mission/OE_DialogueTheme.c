// Original Operation Exile companion code. No Expansion source is included.
class OE_DialogueTheme
{
    string Path;
    string Label;
    string Subtitle;
    string Code;
    string FullName;
    string FrameTexture;

    void OE_DialogueTheme(string path)
    {
        Path = path;
        GetGame().ConfigGetText(Path + " label", Label);
        GetGame().ConfigGetText(Path + " subtitle", Subtitle);
        GetGame().ConfigGetText(Path + " code", Code);
        GetGame().ConfigGetText(Path + " fullName", FullName);
        GetGame().ConfigGetText(Path + " frameTexture", FrameTexture);
    }

    static OE_DialogueTheme Resolve(int npcID, int treeID, bool isTrader = false)
    {
        string root = "CfgOperationExileDialogueThemes";
        int count = GetGame().ConfigGetChildrenCount(root);
        for (int i = 0; i < count; i++)
        {
            string child;
            if (!GetGame().ConfigGetChildName(root, i, child))
                continue;
            string path = root + " " + child;
            if (GetGame().ConfigGetInt(path + " enabled") != 1)
                continue;
            if (GetGame().ConfigGetInt(path + " allTraders") == 1)
            {
                if (isTrader)
                    return new OE_DialogueTheme(path);
                continue;
            }
            if (GetGame().ConfigIsExisting(path + " testNpcID"))
            {
                if (GetGame().ConfigGetInt(path + " testNpcID") == npcID && GetGame().ConfigGetInt(path + " testTreeID") == treeID)
                    return new OE_DialogueTheme(path);
            }
            if (GetGame().ConfigGetInt(path + " npcID") != npcID)
                continue;
            if (GetGame().ConfigGetInt(path + " treeID") != treeID)
                continue;
            return new OE_DialogueTheme(path);
        }
        return null;
    }

    protected array<int> ReadColor(string field, array<int> fallback)
    {
        array<int> values = new array<int>;
        GetGame().ConfigGetIntArray(Path + " " + field, values);
        bool valid = values.Count() == 4;
        foreach (int channel : values)
        {
            if (channel < 0 || channel > 255)
                valid = false;
        }
        if (valid)
            return values;
        values.Clear();
        if (fallback)
        {
            foreach (int component : fallback)
                values.Insert(component);
        }
        return values;
    }

    int Color(string field)
    {
        array<int> fallback = {255, 200, 200, 200};
        array<int> channels = ReadColor(field, fallback);
        return ARGB(channels[0], channels[1], channels[2], channels[3]);
    }

    int FrameTint()
    {
        // Other themes keep the original, untinted texture.
        if (!GetGame().ConfigIsExisting(Path + " FrameTintColor"))
            return ARGB(255, 255, 255, 255);
        array<int> white = {255, 255, 255, 255};
        array<int> channels = ReadColor("FrameTintColor", white);
        return ARGB(channels[0], channels[1], channels[2], channels[3]);
    }

    bool HasBrandColor()
    {
        return GetGame().ConfigIsExisting(Path + " BrandColor");
    }

    float HeaderOffset()
    {
        if (!GetGame().ConfigIsExisting(Path + " HeaderOffsetY"))
            return 0;
        // Restrict the visual offset so it cannot hide the body or footer.
        return Math.Clamp(GetGame().ConfigGetFloat(Path + " HeaderOffsetY"), 0, 0.05);
    }

    DialogueMenuConfig MakeLocalConfig(DialogueMenuConfig source)
    {
        // Never modify DialogueManager's shared menu config: doing so leaks
        // this palette into the next NPC/trader opened by the player.
        DialogueMenuConfig result = new DialogueMenuConfig;
        result.ConfigVersion = source.ConfigVersion;
        result.Position = source.Position;
        result.PanelWidth = 0.64;
        result.PanelHeight = 0.52;
        result.OffsetX = source.OffsetX;
        result.OffsetY = source.OffsetY;
        result.EdgeMargin = source.EdgeMargin;
        result.FontStyle = source.FontStyle;
        result.ShowResponseIcons = source.ShowResponseIcons;
        result.ShowLanguageButton = source.ShowLanguageButton;
        result.ScaleTextWithPanel = source.ScaleTextWithPanel;
        result.ShowErrorNotifications = source.ShowErrorNotifications;
        result.LayoutOverride = source.LayoutOverride;
        result.WindowBorderThickness = 0;
        result.VisitedResponseOpacity = 0.60;
        result.BackgroundColor = ReadColor("BackgroundColor", source.BackgroundColor);
        result.ResponseBackgroundColor = ReadColor("ResponseBackgroundColor", source.ResponseBackgroundColor);
        result.HoverBorderColor = ReadColor("HoverBorderColor", source.HoverBorderColor);
        result.SpeakerNameColor = ReadColor("SpeakerNameColor", source.SpeakerNameColor);
        result.SpeakerTextColor = ReadColor("SpeakerTextColor", source.SpeakerTextColor);
        result.ResponseTextColor = ReadColor("ResponseTextColor", source.ResponseTextColor);
        result.RewardSelectedColor = ReadColor("RewardSelectedColor", source.RewardSelectedColor);
        result.WindowBorderColor = ReadColor("WindowBorderColor", source.WindowBorderColor);
        return result;
    }
};
