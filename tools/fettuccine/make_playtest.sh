#!/bin/zsh
# Build a playtest package for testers.
#
# Run from the project root:
#     tools/fettuccine/make_playtest.sh 3
#
# Before running, write the tester notes in docs/playtests/playtest-3.txt and
# commit everything. The script then:
#   1. builds the ROM with `make` (the normal build, debug menus on),
#   2. makes fettuccine-playtest-3.bps from a clean Emerald ROM and checks it,
#   3. zips the patch with the notes (as README.txt) into
#      ../Fettuccine Playtest 3/fettuccine-playtest-3.zip.
#
# To put it on GitHub afterwards:
#     gh release create playtest-3 "../Fettuccine Playtest 3/fettuccine-playtest-3.zip" \
#         --title "Playtest 3" --notes-file docs/playtests/playtest-3.txt
#
# The clean ROM path can be changed with CLEAN_ROM=/path/to/emerald.gba.

set -e

N=$1
if [[ -z $N ]]; then
    echo "usage: tools/fettuccine/make_playtest.sh <playtest number>"
    exit 1
fi

CLEAN_ROM=${CLEAN_ROM:-"$HOME/Desktop/Roms/Pokemon Roms/Pokemon Emerald Version.gba"}
CLEAN_SHA1=f3ae088181bf583e55daf962a92bb46f4f1d07b7
NOTES=docs/playtests/playtest-$N.txt
OUT_DIR="../Fettuccine Playtest $N"
NAME=fettuccine-playtest-$N

if [[ ! -f $NOTES ]]; then
    echo "error: write the tester notes in $NOTES first"
    exit 1
fi
if [[ -n $(git status --porcelain) ]]; then
    echo "error: commit your changes first, so the playtest matches a saved version"
    exit 1
fi
if [[ $(shasum "$CLEAN_ROM" | cut -d' ' -f1) != $CLEAN_SHA1 ]]; then
    echo "error: $CLEAN_ROM is not a clean US Emerald ROM"
    exit 1
fi

make -j8

mkdir -p "$OUT_DIR"
python3 tools/fettuccine/make_bps.py "$CLEAN_ROM" pokeemerald.gba "$OUT_DIR/$NAME.bps"
cp "$NOTES" "$OUT_DIR/README.txt"
rm -f "$OUT_DIR/$NAME.zip"
(cd "$OUT_DIR" && zip -q "$NAME.zip" "$NAME.bps" README.txt && rm "$NAME.bps" README.txt)

echo "Done: $OUT_DIR/$NAME.zip (built from commit $(git rev-parse --short HEAD))"
