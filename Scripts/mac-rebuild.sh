#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_FILE="$PROJECT_DIR/UnrealPope.uproject"

if [[ ! -f "$PROJECT_FILE" ]]; then
  echo "Could not find UnrealPope.uproject at: $PROJECT_FILE" >&2
  exit 1
fi

# Launcher installs usually live here. UE_5.7 covers 5.7.x patch releases such as 5.7.4.
CANDIDATES=(
  "/Users/Shared/Epic Games/UE_5.7/Engine/Build/BatchFiles/Mac/Build.sh"
  "/Applications/Epic Games/UE_5.7/Engine/Build/BatchFiles/Mac/Build.sh"
)

BUILD_SH="${UNREAL_BUILD_SH:-}"
if [[ -z "$BUILD_SH" ]]; then
  for candidate in "${CANDIDATES[@]}"; do
    if [[ -x "$candidate" ]]; then
      BUILD_SH="$candidate"
      break
    fi
  done
fi

if [[ -z "$BUILD_SH" || ! -x "$BUILD_SH" ]]; then
  echo "Could not find Unreal Build.sh." >&2
  echo "Set UNREAL_BUILD_SH to your Build.sh path, for example:" >&2
  echo "export UNREAL_BUILD_SH='/Users/Shared/Epic Games/UE_5.7/Engine/Build/BatchFiles/Mac/Build.sh'" >&2
  exit 1
fi

echo "Project: $PROJECT_FILE"
echo "Unreal Build.sh: $BUILD_SH"

echo "Cleaning generated Unreal folders..."
rm -rf "$PROJECT_DIR/Binaries" "$PROJECT_DIR/Intermediate" "$PROJECT_DIR/Saved" "$PROJECT_DIR/DerivedDataCache"

echo "Checking local Mac toolchain..."
if command -v xcode-select >/dev/null 2>&1; then
  xcode-select -p || true
fi
if command -v xcodebuild >/dev/null 2>&1; then
  xcodebuild -version || true
  xcodebuild -showsdks || true
fi

echo "Checking Unreal Mac platform support files..."
ENGINE_ROOT="$(cd "$(dirname "$BUILD_SH")/../../.." && pwd)"
MAC_PLATFORM_INFO="$ENGINE_ROOT/Platforms/Mac/Config/DataDrivenPlatformInfo.ini"
MAC_SDK_JSON="$ENGINE_ROOT/Platforms/Mac/Config/SDK.json"
if [[ ! -f "$MAC_PLATFORM_INFO" ]]; then
  echo "Missing Unreal Mac platform info: $MAC_PLATFORM_INFO" >&2
  echo "This Unreal install does not appear to include Mac platform support, or the install is incomplete." >&2
  echo "Open Epic Games Launcher > Unreal Engine > UE_5.7 > Options and make sure Mac platform support is installed, then Verify the engine install." >&2
  exit 2
fi
if [[ ! -f "$MAC_SDK_JSON" ]]; then
  echo "Warning: missing Unreal Mac SDK descriptor: $MAC_SDK_JSON" >&2
fi

echo "Building UnrealPopeEditor for Mac Development..."
"$BUILD_SH" UnrealPopeEditor Mac Development -Project="$PROJECT_FILE" -WaitMutex

echo "Build complete. Now open:"
echo "open '$PROJECT_FILE'"
