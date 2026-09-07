# Operation Exile Dialogue Themes

Custom conversation menus for **Dialogue Framework by ABTT ESK**. Includes UCF, CCA, Green Mountain and trader themes, with textured frames, response colours and Escape-to-close.

**Author:** CtrlQuest / Operation Exile · **Source version:** 0.3.1

## Start here

1. Read [Customise for your server](docs/CUSTOMIZATION.md). Most changes are in `addons/themes/config.cpp`.
2. Follow [Build and install](docs/BUILD.md) to pack the addon.


## Included files

| Location | Purpose |
| --- | --- |
| `addons/themes/config.cpp` | Dependencies, NPC/tree matching, labels, colours and texture paths |
| `addons/themes/$PBOPREFIX$` | Internal addon path; keep it intact |
| `addons/themes/Scripts/5_Mission/` | Theme selection and menu integration |
| `addons/themes/GUI/layouts/` | Menu and response layouts, including font variants |
| `addons/themes/GUI/textures/` | Four frame textures in DayZ PAA format |
| `addons/themes/LICENSE-DialogueFramework.txt` | Preserved upstream MIT notice |
| `mod.cpp` | Launcher name, author, version and description |
| `docs/` | Build, customisation and troubleshooting instructions |

## Requirements

Install **Dialogue Framework** separately, together with its required Expansion components and CF. The inspected framework v1.3.0 documentation lists Expansion Core, Quests, Market and AI (or the Expansion Bundle), plus CF.

The addon declares `DialogueFramework` in `requiredAddons` and extends its `DialogueWindowMenu`. Framework API changes can require updates to this addon. See the [upstream project](https://github.com/ABTT-ESK/DayZ-DialogueFramework-Release) for its release instructions.

## Scope and status

- Included defaults match Operation Exile's NPC/tree IDs; change them for another server.
- This package does not spawn NPCs, create quests, or install server dialogue JSON.
- UCF, CCA and GM select menus by NPC/tree IDs. These names do **not** restrict access by player faction.
- Trader styling applies to all recognised framework trader sessions. Individual trader themes need a script change.
- The supplied screenshots show the original addon in game.
