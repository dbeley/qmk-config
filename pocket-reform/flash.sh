#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
#
# Flash the Pocket Reform keyboard firmware built from this keymap.
#
# The keyboard cannot type once it is in flash mode, so this arms the flash
# first, tells you when the bootloader is actually seen, and only then writes.
#
#   ./flash.sh [file.uf2]        (default: ~/src/qmk_firmware/mntre_pocket_reform_hid_dbeley.uf2)

set -euo pipefail

uf2="${1:-$HOME/src/qmk_firmware/mntre_pocket_reform_hid_dbeley.uf2}"
wait_for=180

if ! command -v picotool >/dev/null; then
    echo "picotool is not in PATH. Run this from:" >&2
    echo "  nix shell nixpkgs#picotool" >&2
    exit 1
fi
if [ ! -f "$uf2" ]; then
    echo "no such firmware file: $uf2" >&2
    exit 1
fi

echo "firmware: $uf2 ($(stat -c %s "$uf2") bytes)"
echo
echo "== step 1: put the keyboard in flash mode =="
echo "   hold HYPER (bottom left) + Enter -> menu -> X -> confirm"
echo "   The keyboard stops typing once it is in flash mode; you have ${wait_for}s."
echo

# Cache the sudo password while the keyboard still works, so nothing asks for
# it later, when the keyboard can no longer type.
sudo -v
echo "== step 2: waiting for the RP2040 bootloader =="
printf '   '
detected=0
for _ in $(seq 1 "$wait_for"); do
    if sudo -n picotool info -q >/dev/null 2>&1; then
        detected=1
        break
    fi
    printf '.'
    sleep 1
done
echo

if [ "$detected" -ne 1 ]; then
    echo "   no RP2040 in flash mode after ${wait_for}s, nothing was written." >&2
    echo "   power-cycle the keyboard (or double-press RESET under the top cover) and retry." >&2
    exit 1
fi

echo "   detected:"
sudo -n picotool info 2>&1 | sed 's/^/     /' | head -8
echo
echo "== step 3: writing (verify pass included, a few seconds) =="
sudo -n picotool load -x -v "$uf2"
echo
echo "== step 4: done, the keyboard rebooted into the new firmware =="
echo "   if it stayed in flash mode instead, run: sudo picotool reboot"
