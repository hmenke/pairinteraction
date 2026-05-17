#!/usr/bin/env bash

set -euo pipefail

if [ "$#" -ne 4 ]; then
  printf 'Usage: %s <app-path> <version> <arch> <output-dir>\n' "$0" >&2
  exit 1
fi

app_path="$1"
version="$2"
arch="$3"
output_dir="$4"

mkdir -p "$output_dir"

stage_dir="$(mktemp -d)"
trap 'rm -rf "$stage_dir"' EXIT

cp -R "$app_path" "$stage_dir/"
ln -s /Applications "$stage_dir/Applications"

output_path="$output_dir/PairInteraction-${version}-macos-${arch}.dmg"

hdiutil create \
  -volname "PairInteraction" \
  -srcfolder "$stage_dir" \
  -ov \
  -format UDZO \
  "$output_path"

printf '%s\n' "$output_path"
