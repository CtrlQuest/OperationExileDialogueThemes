# Build and install

## 1. Prepare the source

Install DayZ Tools and open Addon Builder. Keep this repository as your editable source and put packed output in a separate folder.

For a straightforward P-drive setup, copy **the contents of `addons/themes`** into:

`P:\operationexiledialoguethemes\addons\themes\`

That folder must directly contain `config.cpp`, `$PBOPREFIX$`, `Scripts`, `GUI` and the licence notice. Do not pack the repository root.

The PBO's virtual prefix must be:

`operationexiledialoguethemes\addons\themes`

The included `$PBOPREFIX$` records that value. If your packer has an explicit addon-prefix option, set it to the same value. Keep the filename extensionless; Windows must not save it as `$PBOPREFIX$.txt`.

## 2. Pack

Use these settings for this source package:

| Setting | Value |
| --- | --- |
| Source directory | `P:\operationexiledialoguethemes\addons\themes` |
| Destination directory | A separate `@OperationExileDialogueThemes\addons` folder |
| Addon prefix | `operationexiledialoguethemes\addons\themes` |
| Binarize | Off for the initial build; supplied config and layouts are text, textures are already PAA |
| Copy directly | Ensure `*.c;*.cpp;*.layout;*.paa;*.txt` are included; retain any other patterns you need |

Addon Builder's copy list determines which source files are copied into the packed addon; see [Bohemia's Addon Builder documentation](https://community.bistudio.com/wiki/Addon_Builder). General setup is covered in [DayZ Modding Basics](https://community.bistudio.com/wiki/DayZ:Modding_Basics).

Pack the addon. If the tool names the output `themes.pbo`, rename it to `OperationExileDialogueThemes_themes.pbo` **before signing**. Copy the repository's `mod.cpp` beside the output `addons` folder, not inside the PBO.

Inspect the built PBO once: `config.cpp`, `Scripts/5_Mission`, `GUI/layouts`, `GUI/textures` and the licence notice should be directly inside it, with the prefix above. An extra nested `themes` directory inside the PBO will break the referenced paths. Never load both the old and new copies of the addon.

## 3. Sign and deploy

Sign the final PBO with your own signing key using DayZ Tools. Distribute its matching `.bisign` beside the PBO and install the public `.bikey` in the server's `keys` folder. Keep the private `.biprivatekey` outside the repository and Workshop upload. The original signature cannot validate a rebuilt PBO.

| Release file | Destination |
| --- | --- |
| `mod.cpp` | `@OperationExileDialogueThemes/mod.cpp` |
| Built PBO | `@OperationExileDialogueThemes/addons/` |
| Matching `.bisign` | Beside that PBO |
| Your public `.bikey` | Server `keys/`; optionally include a `keys/` folder in the release |

Load the addon on **server and clients**, after Dialogue Framework and its dependencies in the normal `-mod` list. A client UI addon cannot be supplied only through `-serverMod`.

For Workshop testing, upload the **packed release folder**, not this source repository. Set Dialogue Framework as a required item and follow its dependency instructions. This repository deliberately excludes `meta.cpp`: another server should publish its own item rather than reuse Operation Exile's Workshop identity. The owner updating the existing item should select that item in their own publisher setup.

## 4. Check in game

1. First confirm the chosen NPC can open a working Dialogue Framework conversation.
2. Set that NPC's ID and its active dialogue tree's top-level `ID` in the theme config; rebuild and deploy matching copies.
3. Open the NPC. Check the frame, title and colours; choose replies and close with Escape and the close button.
4. Open another themed NPC, then an unthemed one, to check selection and palette reset.
5. Test a trader, long replies, quest/reward screens and the framework font options used by your players.

This verifies the rebuilt version on your dependency versions. No automated source check can replace DayZ's script compilation and in-game UI checks.

## Troubleshooting

| Symptom | Check |
| --- | --- |
| Framework script/class missing | Framework is loaded first on both sides; its API matches the addon |
| Normal framework menu appears | Theme `enabled = 1`; both IDs match; `MenuConfig.json` has an empty `LayoutOverride` |
| Wrong theme appears | Duplicate ID pairs or a leftover GM test alias; first enabled match wins |
| Texture/layout missing | PBO prefix, included file types, exact paths and four PAA textures |
| Trader keeps default menu | Expansion Market and framework trader dialogue work; `allTraders = 1` |
| Changed JSON colours do nothing | Theme palette is packed in `config.cpp`; rebuild to change it |
| Panel size ignores JSON | This version hardcodes themed width/height in `MakeLocalConfig` |
| Old appearance after an update | Updated PBO reached the client; duplicate addon removed; client restarted |
| Signature mismatch | Re-sign the final PBO and deploy the matching signature/public key |

Check client script logs for `[OperationExileDialogueThemes] v0.3.1 NPC=... theme=...`. If the conversation itself does not load, inspect the framework's server `DialogFramework/Dialogues/LoadLog.txt`.
