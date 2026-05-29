#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_FILE="$PROJECT_DIR/UnrealPope.uproject"

if [[ ! -f "$PROJECT_FILE" ]]; then
  echo "Could not find UnrealPope.uproject at: $PROJECT_FILE" >&2
  exit 1
fi

export DEVELOPER_DIR="${DEVELOPER_DIR:-/Applications/Xcode.app/Contents/Developer}"

if ! xcrun --find metal >/dev/null 2>&1; then
  echo "Xcode Metal Toolchain is missing. Install it with:" >&2
  echo "  sudo xcodebuild -downloadComponent MetalToolchain" >&2
  exit 2
fi

METAL_BIN_DIR="$(dirname "$(xcrun --find metal)")"
export PATH="$METAL_BIN_DIR:$PATH"

echo "Developer dir: $(xcode-select -p)"
echo "Metal compiler: $(xcrun --find metal)"
echo "Opening Unreal project with Metal toolchain on PATH..."
open "$PROJECT_FILE"
