# Pocket Reform — QMK keyboard

Two layouts in one firmware for the MNT Pocket Reform's built-in keyboard:

- **BASE** — the stock layout with modifiers added on the right side, arrows moved
  to the HYPER layer.
- **MIRYOKU** — Miryoku (Colemak-DH, home-row mods, 10 layers), toggled at runtime.

Design: `design.md`. Implementation plan: `plan.md`.

## Hardware/firmware stack

The keyboard/trackball controller is an RP2040 on the HID board, driven by the
community QMK port [`sleeplessval/qmk-pocket-reform`](https://codeberg.org/sleeplessval/qmk-pocket-reform)
(keyboard name `mntre/pocket_reform_hid`). Nothing in the port is modified: all
our code lives in this directory and is installed as `keymaps/dbeley/`.

Pinned versions (update these notes when bumping):

| Component | Revision |
| --- | --- |
| `qmk/qmk_firmware` | `d194c077ed964195ec16d255c7a4b89a794cf03b` (2026-11-08) |
| `sleeplessval/qmk-pocket-reform` | `75057bb26ff4cdb6744a5c7e0db87a2fc8f8228c` (2026-10-23) |

## One-time setup

Toolchain from nixpkgs (all available from the binary cache on aarch64):

```sh
nix shell nixpkgs#qmk nixpkgs#gcc-arm-embedded nixpkgs#picotool
```

`arm-none-eabi-gcc 15.3` builds this port cleanly; no older toolchain needed.

```sh
mkdir -p ~/src && cd ~/src
git clone https://github.com/qmk/qmk_firmware.git
git -C qmk_firmware checkout d194c077ed964195ec16d255c7a4b89a794cf03b

# RP2040 builds need these submodules (shallow clones are fine)
cd qmk_firmware
git submodule update --init --depth 1 \
  lib/pico-sdk lib/printf lib/chibios lib/chibios-contrib lib/lufa
cd ~/src

# upstream ships keyboards/mntre (the classic Reform keyboard) — move it out of
# the build tree and install the port in its place
git clone https://codeberg.org/sleeplessval/qmk-pocket-reform.git
git -C qmk-pocket-reform checkout 75057bb26ff4cdb6744a5c7e0db87a2fc8f8228c
mkdir -p disabled && mv qmk_firmware/keyboards/mntre disabled/mntre
mv qmk_firmware/keyboards/mntre_v3 disabled/mntre_v3
mkdir -p qmk_firmware/keyboards/mntre
cp -r qmk-pocket-reform qmk_firmware/keyboards/mntre/pocket_reform_hid
```

## Build

```sh
nix shell nixpkgs#qmk nixpkgs#gcc-arm-embedded -c \
  qmk compile -kb mntre/pocket_reform_hid -km dbeley
```

`install.sh` installs this directory as `keymaps/dbeley/` in an existing QMK
tree. The CLI route (`qmk compile`) works with an external `QMK_HOME`; `make`
from inside the tree works too but needs the python deps in the shell.

## Flash

Bootloader routes, easiest first:

1. **Menu**: hold the bottom-left key (HYPER) and press Enter, then `X`, then
   confirm. Works from BASE and from HYPER.
2. **Keycode**: `QK_BOOT` on the HYPER layer (row 2, column 4).
3. **Hardware**: open the top cover and double-press RESET on the OLED board.

Then, on the pocket:

```sh
nix shell nixpkgs#picotool -c bash -c \
  'sudo picotool load mntre_pocket_reform_hid_dbeley.uf2 && sudo picotool reboot'
```

## Layout

Switching: **HYPER + Shift + M** enters MIRYOKU; the bottom-left key (`BACK`)
returns to BASE. The choice persists across reboots (`QK_CLEAR_EEPROM` lives on
MIRYOKU's Fun layer). The OLED names the active layout.

BASE:

```
ESC 1 2 3 4 5 6 7 8 9 0 ⌫
TAB q w e r t y u i o p ;
CTL a s d f g h j k l ' ⏎
SFT z x c v b n m , .  ↑  RSFT
MO  ◆ ⌥ \ = ␣ ␣  - /  RALT ↓  RCTL
        M3 M1        SCRL M2
```

HYPER additionally gives `H/J/K/L` = ← ↓ ↑ → and `↑` = Page Up.
