# Unreal Pope — UE 5.7 Cinematic Prototype

Created by ZEUS as a clean Unreal Engine 5.7-ready C++ starter project.

## Vision

A cinematic third/first-person Unreal prototype foundation: atmospheric exploration, interactable relic-style objects, extensible player systems, and production-safe Git structure for real UE development.

This repository currently contains source/config scaffolding only. Open it on the Mac mini with Unreal Engine 5.7 installed to generate project files, compile, and begin creating assets/maps.

## Included

- Unreal Engine `5.7` `.uproject`
- C++ runtime module: `UnrealPope`
- Player character with Enhanced Input hooks
- Player controller prepared for input mapping context
- Interaction component with line trace detection
- Interactable actor base class
- Game mode bootstrap
- Unreal `.gitignore`
- Git LFS `.gitattributes` for `.uasset`, `.umap`, media, textures, and models
- Config defaults for map/game mode/input readiness

## Mac mini setup

Install prerequisites:

```bash
brew install git git-lfs
git lfs install
```

Clone:

```bash
git clone https://github.com/waitholdthis/unreal_pope.git
cd unreal_pope
```

A fresh C++ Unreal repo does not commit `Binaries/`, so Unreal may say the `UnrealPope` module is missing or built with a different engine version. That is normal until the module is compiled locally.

Manual rebuild:

```bash
chmod +x Scripts/mac-rebuild.sh
./Scripts/mac-rebuild.sh
```

Then open through the helper so Unreal inherits the Xcode/Metal toolchain environment:

```bash
chmod +x Scripts/mac-open-editor.sh
./Scripts/mac-open-editor.sh
```

If you prefer opening directly and the editor reports a missing Metal Toolchain, launch through `Scripts/mac-open-editor.sh` instead of double-clicking the `.uproject`.

If your Unreal install is not in the default Launcher path, set `UNREAL_BUILD_SH` first:

```bash
export UNREAL_BUILD_SH="/Users/Shared/Epic Games/UE_5.7/Engine/Build/BatchFiles/Mac/Build.sh"
./Scripts/mac-rebuild.sh
```

If Unreal asks to rebuild modules, choose yes.

## Recommended first Unreal Editor steps

1. Open `UnrealPope.uproject` in UE 5.7.
2. Let Unreal generate IDE/project files.
3. Create a default map at `Content/Maps/L_CathedralPrototype.umap`.
4. Set it as the default map in Project Settings or `Config/DefaultEngine.ini`.
5. Create Enhanced Input assets:
   - `Content/Input/IMC_Player.uasset`
   - `Content/Input/IA_Move.uasset`
   - `Content/Input/IA_Look.uasset`
   - `Content/Input/IA_Interact.uasset`
6. Subclass `AZeusPlayerController` / `AZeusCharacter` in Blueprint if desired.
7. Add interactable objects by subclassing `AZeusInteractableActor`.

## Notes

This repo intentionally excludes generated folders:

- `Binaries/`
- `Intermediate/`
- `Saved/`
- `DerivedDataCache/`

Those are rebuilt locally by Unreal and should not be committed.
