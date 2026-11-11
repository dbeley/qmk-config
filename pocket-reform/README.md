# Pocket Reform — QMK keyboard

Two layouts in one firmware for the MNT Pocket Reform's built-in keyboard:

- **BASE** — the stock layout with modifiers added on the right side, arrows moved
  to the HYPER layer.
- **MIRYOKU** — Miryoku (home-row mods, 10 layers), toggled at runtime, with two
  interchangeable alpha sets: Colemak-DH and Gallium.

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

Bootloader: hold the bottom-left key (HYPER) and press Enter, `X`, then confirm.
Last resort: open the top cover and double-press RESET on the OLED board.

The keyboard cannot type once it is in flash mode, so arm the flash first and
use the delay to press the keys. Enter BASE first: the menu selects its entries
by keycode (`X` flashes, `1`/`0` power, `B` battery), which are different
physical keys in Colemak-DH.

Ran those commands all at once:
```sh
nix shell nixpkgs#picotool
sudo -v
sleep 60
# put the keyboard in flash mode here
sudo picotool load -x -v ~/src/qmk_firmware/mntre_pocket_reform_hid_dbeley.uf2
```

## Backlight

QMK boots the RGB off (`RGBLIGHT_DEFAULT_ON` in our `config.h` turns it back
on, but the rgb state is stored in EEPROM, so an already-booted keyboard needs
one press of `HYPER + \` (toggle), `HYPER + =` / `HYPER + -` (brightness)).

The stylix colour is sent by `nixos-mnt-pocket-reform`'s keyboard module as a
QMK raw HID output report.

## Tap-hold behaviour

`CHORDAL_HOLD` (QMK core) decides home-row mods and layer thumbs by hand rather
than by clock: a second key on the **same hand** makes the first one a tap, a
second key on the **other hand** makes it a hold (with `PERMISSIVE_HOLD`). Typing
rolls therefore stop producing stray modifiers, while Miryoku's
hold-a-thumb-on-the-opposite-hand rule keeps working as designed.

The hand map is `chordal_hold_layout` in `keymap.c`: columns 1-6 left, 7-12
right (the same place the six Miryoku thumbs split), the four thumb buttons
exempt so trackball clicks never join a chord.

## Layout

Switching: **HYPER + Shift + M** enters MIRYOKU with Colemak-DH alphas,
**HYPER + Shift + G** enters the same skeleton with Gallium alphas; the
bottom-left key (`BACK`) returns to BASE from either. The choice persists across
reboots (`QK_CLEAR_EEPROM` lives on MIRYOKU's Fun layer).

Gallium (`_M_BASE_GALLIUM`), the columnar-staggered variant, with the same six
thumbs and the same home-row mod positions:

```
B L D C V  ·  J Y O U ,
N R T S G  ·  P H A E I
X Q M W Z  ·  K F ' ; .
```

Gallium pushes `/` out of its 3x10 block, so it lands on column 10 of the
bottom row (a key Miryoku leaves dead).

MIRYOKU's bottom row (row 5):

```
physical:   ⌥     \      =     Space  Space    -      /   AltGr
MIRYOKU:    ·   Esc    Space   Tab    Enter   Bksp   Del     ·
                Media   Nav    Mouse   Sym     Num    Fun
```

`BACK` sits on the bottom-left key (the HYPER key's position in BASE); columns
10-12 of that row, all of column 6-7 in rows 1-3 and the whole 4th row are inert.

BASE:

```
ESC 1 2 3 4 5 6 7 8 9 0 ⌫
TAB q w e r t y u i o p ;
CTL a s d f g h j k l ' ⏎
SFT z x c v b n m , .  ↑  RSFT
MO  ◆ ⌥ \ = ␣ ␣  - /  RALT ◆  RCTL
        M3 M1        SCRL M2
```

HYPER, matching MNT's stock function layer where it can:

```
`  F1..F10  DEL        (HYPER + Backspace = Delete, as in the stock firmware)
   F11 F12 F13
   ← ↓ ↑ →  MENU      (arrows replaced the stock H/J/K/L; Enter opens the menu)
   PGUP RSFT  (↑ position)
   RGB V+ V- HOME PGDN END
```

`UG_TOGG` on `\`, brightness on `=` / `-` take the place of the stock
backslash/equal/minus, which are unchanged on BASE. Nothing on any layer drops
the keyboard into flash mode.
