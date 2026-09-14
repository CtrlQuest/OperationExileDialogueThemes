# Operation Exile Dialogue Themes

Custom conversation menus for **Dialogue Framework by ABTT ESK**. Includes UCF, CCA, Green Mountain and trader themes, with textured frames, response colours and Escape-to-close.

**Author:** CtrlQuest / Operation Exile · **Source version:** 0.3.3

## Template use

This repository contains the dialogue theme setup currently used on the live **Operation Exile** DayZ server.

It is provided as a template and working example for server owners who want to create their own custom themes for the [DayZ Dialogue Framework](https://github.com/ABTT-ESK/DayZ-DialogueFramework-Release).

You are welcome to use this project as a starting point to build and customise your own faction, network, trader and NPC dialogue themes.

The included **UCF, CCA, Green Mountain and trader names, IDs, branding and styling** are taken from the live Operation Exile server and are connected to our active lore and ongoing storyline.

If you use this project on your own server, please replace the Operation Exile names, branding, NPC/tree IDs and themes with your own rather than copying the live server setup directly.

The included themes are intended to demonstrate how the system works and provide a working base for you to build from.

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
- Included faction, network and trader names and styling are part of Operation Exile's active server setup and lore.
- This package does not spawn NPCs, create quests, or install server dialogue JSON.
- UCF, CCA and GM select menus by NPC/tree IDs. These names do **not** restrict access by player faction.
- Trader styling applies to all recognised framework trader sessions. Individual trader themes need a script change.
- The supplied screenshots show the original addon in game.
