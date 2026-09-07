// Operation Exile companion. The framework still owns dialogue and quest actions.
modded class DialogueWindowMenu
{
    protected ref OE_DialogueTheme m_OETheme;
    protected ref DialogueMenuConfig m_OELocalConfig;
    protected bool m_OEThemeResolved;
    protected bool m_OEFrameLoaded;
    protected bool m_OECloseQueued;

    protected void OE_ResolveTheme()
    {
        if (m_OEThemeResolved || !m_MenuConfig)
            return;
        m_OEThemeResolved = true;
        // An explicit third-party layout remains authoritative.
        bool isTrader = false;
        #ifdef EXPANSIONMODMARKET
        // A stale trader session must not theme an unrelated quest NPC.
        if (m_NPCID == -1 && DialogueTraderSession.s_Trader)
            isTrader = true;
        #endif
        if (m_ActiveTree && m_MenuConfig.LayoutOverride == "")
            m_OETheme = OE_DialogueTheme.Resolve(m_NPCID, m_ActiveTree.ID, isTrader);
        if (m_OETheme)
        {
            m_OELocalConfig = m_OETheme.MakeLocalConfig(m_MenuConfig);
            Print("[OperationExileDialogueThemes] v0.3.1 NPC=" + m_NPCID + " theme=" + m_OETheme.Code);
        }
    }

    override protected string LayoutPath(string baseName)
    {
        // Init asks for its layout before ApplyMenuConfig is called.
        OE_ResolveTheme();
        if (m_OETheme && (baseName == "dialogue_menu" || baseName == "dialogue_response_button"))
            return "operationexiledialoguethemes/addons/themes/GUI/layouts/" + baseName + m_LayoutSuffix + ".layout";
        return super.LayoutPath(baseName);
    }

    override protected void ApplyMenuConfig()
    {
        OE_ResolveTheme();
        if (m_OELocalConfig)
            m_MenuConfig = m_OELocalConfig;
        super.ApplyMenuConfig();
        if (m_OETheme)
            OE_ApplyChrome();
    }

    protected void OE_ApplyChrome()
    {
        if (!layoutRoot || !m_DialoguePanel || !m_OELocalConfig)
            return;
        Widget frame = layoutRoot.FindAnyWidget("OEWindow");
        if (!frame)
            return;
        // Use screen space to avoid interface-scale multiplication. DialoguePanel
        // remains the framework's inner body for its quest/reward calculations.
        float screenW;
        float screenH;
        float rootX;
        float rootY;
        layoutRoot.GetScreenSize(screenW, screenH);
        layoutRoot.GetScreenPos(rootX, rootY);
        if (screenW <= 0 || screenH <= 0)
            return;
        string serverPosition = m_OELocalConfig.Position;
        string playerPosition = DialogueClientSettings.Get().Position;
        if (playerPosition != "")
            m_OELocalConfig.Position = playerPosition;
        float x;
        float y;
        m_OELocalConfig.GetResolvedPosition(x, y);
        m_OELocalConfig.Position = serverPosition;
        x = Math.Clamp(x, 0.01, 1.0 - m_OELocalConfig.PanelWidth - 0.01);
        y = Math.Clamp(y, 0.01, 1.0 - m_OELocalConfig.PanelHeight - 0.01);
        frame.SetScreenSize(screenW * m_OELocalConfig.PanelWidth, screenH * m_OELocalConfig.PanelHeight);
        frame.SetScreenPos(rootX + screenW * x, rootY + screenH * y);
        float headerOffset = m_OETheme.HeaderOffset();
        // Absolute positions are reapplied on Show/settings changes. Never add
        // to current positions: reopening settings must not cause downward drift.
        OE_Position("OEHeaderPlate", 0.03, 0.04 + headerOffset);
        OE_Position("OECode", 0.045, 0.033 + headerOffset);
        OE_Position("OEFullName", 0.045, 0.12 + headerOffset);
        OE_Position("OEBrandDivider", 0.225, 0.055 + headerOffset);
        OE_Position("OEHeading", 0.255, 0.055 + headerOffset);
        OE_Position("OEHeaderRule", 0.025, 0.175 + headerOffset);
        // These two retain their layout's right-aligned, pixel-based X values.
        OE_Position("SettingsButton", 78, 0.065 + headerOffset);
        OE_Position("CloseButton", 38, 0.065 + headerOffset);
        m_DialoguePanel.SetPos(0.04, 0.20 + headerOffset);
        m_DialoguePanel.SetSize(0.92, 0.70 - headerOffset);

        ImageWidget texture = ImageWidget.Cast(layoutRoot.FindAnyWidget("OEFrameTexture"));
        if (texture && !m_OEFrameLoaded)
        {
            texture.LoadImageFile(0, m_OETheme.FrameTexture);
            texture.SetImage(0);
            m_OEFrameLoaded = true;
        }
        if (texture)
            texture.SetColor(m_OETheme.FrameTint());
        OE_Label("OECode", m_OETheme.Code, "SpeakerNameColor");
        OE_Label("OEFullName", m_OETheme.FullName, "AccentColor");
        OE_Label("OEHeading", m_OETheme.Label, "SpeakerTextColor");
        OE_Label("OEFooter", m_OETheme.Subtitle, "AccentColor");
        OE_Label("OEEscapeHint", "ESC  /  CLOSE", "SpeakerNameColor");
        OE_ColorWidget("OEHeaderPlate", "HeaderColor");
        OE_ColorWidget("OEHeaderRule", "WindowBorderColor");
        OE_ColorWidget("OEFooterRule", "WindowBorderColor");
        OE_ColorWidget("OEBrandDivider", "WindowBorderColor");
        OE_ColorWidget("ConfirmPanel", "BackgroundColor");
        OE_ColorWidget("ConfirmText", "SpeakerTextColor");
        OE_ColorWidget("ConfirmYesBackground", "ResponseBackgroundColor");
        OE_ColorWidget("ConfirmNoBackground", "ResponseBackgroundColor");
        OE_ColorWidget("ConfirmYesLabel", "ResponseTextColor");
        OE_ColorWidget("ConfirmNoLabel", "ResponseTextColor");
        OE_ColorWidget("SettingsButtonBackground", "WindowBorderColor");
        OE_ColorWidget("CloseButtonBackground", "WindowBorderColor");
        OE_ColorWidget("SettingsButtonLabel", "SpeakerNameColor");
        OE_ColorWidget("CloseButtonLabel", "SpeakerNameColor");
        if (m_OETheme.HasBrandColor())
        {
            // Cream wordmark/control lettering, with olive reserved for accents.
            OE_ColorWidget("OECode", "BrandColor");
            OE_ColorWidget("OEFullName", "BrandColor");
            OE_ColorWidget("OEEscapeHint", "BrandColor");
            OE_ColorWidget("SettingsButtonLabel", "BrandColor");
            OE_ColorWidget("CloseButtonLabel", "BrandColor");
            OE_ColorWidget("SettingsButtonBackground", "ResponseBackgroundColor");
            OE_ColorWidget("CloseButtonBackground", "ResponseBackgroundColor");
        }
    }

    protected void OE_Position(string name, float x, float y)
    {
        Widget widget = layoutRoot.FindAnyWidget(name);
        if (widget)
            widget.SetPos(x, y);
    }

    protected void OE_Label(string name, string value, string colorField)
    {
        TextWidget label = TextWidget.Cast(layoutRoot.FindAnyWidget(name));
        if (label)
        {
            label.SetText(value);
            label.SetColor(m_OETheme.Color(colorField));
        }
    }

    protected void OE_ColorWidget(string name, string field)
    {
        Widget widget = layoutRoot.FindAnyWidget(name);
        if (widget)
            widget.SetColor(m_OETheme.Color(field));
    }

    override protected void LayoutResponseArea(float topY)
    {
        super.LayoutResponseArea(topY);
        if (!m_OETheme || !m_SpeakerLineScroll)
            return;
        // Quest tiles retain their original area; normal conversations use a
        // taller briefing, with the first choice directly underneath.
        float lineHeight = 0.27;
        if (topY > 0)
            lineHeight = 0.17;
        m_SpeakerLineScroll.SetSize(0.98, lineHeight);
        OE_FitSpeakerText();
    }

    override protected void SetSpeakerLine(string text)
    {
        super.SetSpeakerLine(text);
        if (m_OETheme)
            OE_FitSpeakerText();
    }

    protected void OE_FitSpeakerText()
    {
        if (!m_SpeakerLine || !m_SpeakerLineScroll)
            return;
        // Measure rendered text instead of forcing it to fill the viewport,
        // which can create a permanent scrollbar on scaled clients.
        float width;
        float height;
        m_SpeakerLineScroll.GetScreenSize(width, height);
        if (width <= 0 || height <= 0)
            return;
        m_SpeakerLine.SetScreenSize(width * 0.97, height);
        m_SpeakerLine.Update();
        int textW;
        int textH;
        m_SpeakerLine.GetTextSize(textW, textH);
        if (textH > 0)
            m_SpeakerLine.SetScreenSize(width * 0.97, textH + 4);
        m_SpeakerLineScroll.Update();
    }

    override protected Widget CreateResponseButton(string text, bool visited = false, string iconName = "")
    {
        Widget button = super.CreateResponseButton(text, visited, iconName);
        if (m_OETheme && button)
        {
            array<string> edges = {"OEIdleTop", "OEIdleBottom", "OEIdleLeft", "OEIdleRight"};
            foreach (string edgeName : edges)
            {
                Widget edge = button.FindAnyWidget(edgeName);
                if (edge)
                    edge.SetColor(m_OETheme.Color("WindowBorderColor"));
            }
            Widget rail = button.FindAnyWidget("OEIdleRail");
            if (rail)
                rail.SetColor(m_OETheme.Color("AccentColor"));
        }
        return button;
    }

    override protected float SizeResponseButton(Widget button, TextWidget label, string text, bool hasIcon)
    {
        float height = super.SizeResponseButton(button, label, text, hasIcon);
        if (!m_OETheme || height <= 0)
            return height;
        // Preserve upstream wrapping, translations and icon sizing; add padding.
        height = height + 10;
        button.SetSize(0.98, height);
        return height;
    }

    override protected void EndConversation()
    {
        // X, dialogue options and Escape share one deferred, guarded close.
        if (m_OECloseQueued)
            return;
        m_OECloseQueued = true;
        super.EndConversation();
    }

    override bool OnKeyDown(Widget w, int x, int y, int key)
    {
        if (key == KeyCode.KC_ESCAPE && IsVisible() && !GetSubMenu())
        {
            EndConversation();
            return true;
        }
        return super.OnKeyDown(w, x, y, key);
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);
        // Also honour re-bound UI Back / controller Back. Settings submenus
        // retain their own input handling and are not closed from underneath.
        if (IsVisible() && !GetSubMenu() && GetUApi().GetInputByID(UAUIBack).LocalPress())
            EndConversation();
    }

    override void OnShow()
    {
        m_OECloseQueued = false;
        super.OnShow();
        if (m_OETheme)
        {
            OE_ApplyChrome();
            OE_FitSpeakerText();
        }
    }
};
