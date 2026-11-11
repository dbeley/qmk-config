# Pocket Reform keyboard — one firmware, two layouts

Status: draft for approval.

## Goal

Replace the MNT Pocket Reform keyboard firmware with QMK so that a single
firmware holds two interchangeable layouts:

1. **BASE** — the stock layout with modifiers added on the right side, arrows
   moved off the base layer.
2. **MIRYOKU** — Miryoku (Colemak-DH alphas, home-row mods, 10 layers),
   toggled at runtime; every key outside the Miryoku block is inert.

The trackball and its four buttons keep working identically in both layouts,
and the OLED keeps working in both layouts.

## Decisions taken

| Decision | Choice |
| --- | --- |
| Firmware | [sleeplessval/qmk-pocket-reform](https://codeberg.org/sleeplessval/qmk-pocket-reform) (QMK keyboard `mntre/pocket_reform_hid`), pinned to a commit |
| Where the keymap lives | `qmk-config/pocket-reform/`, installed into a QMK tree by `install.sh` |
| Miryoku source | its generated layer tables copied verbatim into our keymap (`MIRYOKU_ALTERNATIVES_*`), not the 54k-file miryoku fork |
| Miryoku alpha block | physical rows 1–3 (number row / QWER / ASDF), horizontally as wide as the board allows |
| Miryoku thumbs | row 5, centre six keys (directly above the four small thumb keys) |
| Miryoku dead keys | row 4 entirely, columns 6–7 of rows 1–3, outer columns of row 5 |
| Trackball keys | the four small keys below row 5 are never remapped (`MS_BTN1/2/3`, `MNT_SCRL`) |
| OLED | stays functional; adds a layout indicator and optional animation |
| Backlight colour from the host | QMK raw HID report from `nixos-mnt-pocket-reform`'s keyboard module (replaces MNT's `xLRGB`/`xLBRT`) |

## BASE layer

```
ESC 1 2 3 4 5 6 7 8 9 0 ⌫
TAB q w e r t y u i o p ;
CTL a s d f g h j k l ' ⏎
SFT z x c v b n m , .  ↑  RSFT        ← RALT key becomes RShift
MO  ◆ ⌥ \ = ␣ ␣  - /  RALT ◆  RCTL    ← AltGr · Meta · Ctrl on the right
        M3 M1        SCRL M2          ← trackball: untouched
```

* `MO` (bottom-left) is the HYPER layer key, as in the port's stock keymap.
* `MNT_MENU` stays on Hyper+Enter, so the OLED menu keeps its usual shortcut.
* Arrows move to HYPER: `H/J/K/L` → ← ↓ ↑ →, `↑` stays Page Up, and the
  Home/End/PgDn keys already on HYPER (`←`/`↓`/`→`) are freed up and can go
  back to ← / ↓ / → on the same physical keys.

## MIRYOKU layers

Layer ids (Miryoku's own tables use `U_*` names, so we alias them):

```
0 BASE        1 HYPER
2 M_BASE      3 M_EXTRA     4 M_TAP      5 M_BUTTON   6 M_NAV
7 M_MOUSE     8 M_MEDIA     9 M_NUM     10 M_SYM     11 M_FUN
U_BASE/U_EXTRA/U_TAP/U_BUTTON/U_NAV/U_MOUSE/U_MEDIA/U_NUM/U_SYM/U_FUN → the above
U_NA, U_NP → KC_NO
```

```
        col 1  2  3  4  5   6  7   8  9 10 11 12
row1     ·     ·  ·  ·  ·  ██ ██  ·  ·  ·  ·   ·     Colemak-DH top row
row2     ·     ·  ·  ·  ·  ██ ██  ·  ·  ·  ·   ·     home row mods
row3     ·     ·  ·  ·  ·  ██ ██  ·  ·  ·  ·   ·     Colemak-DH bottom row
row4     ██    ██ ██ ██ ██ ██ ██  ██ ██ ██ ██ ██     inert
row5     BACK  ██ ·  ·  ·  ·  ·   ·  ·  ██ ██ ██     thumbs = cols 3–8
thumb     M3 M1                     SCRL M2          untouched
```

* Thumb keys are Miryoku's six `LT(U_*, KC_*)` keys (Fun/Num/Sym on the left,
  Mouse/Nav/Media on the right).
* `BACK` = `DF(BASE)`: return to the base layout, on the same physical key as
  the HYPER layer key in BASE (bottom-left).
* `QK_BOOT` and `QK_CLEAR_EEPROM` stay reachable in MIRYOKU mode (M_FUN layer,
  next to Miryoku's own boot entry) so the layout can never strand the device.
* Alpha choice stays configurable via Miryoku's own flags (`MIRYOKU_ALPHAS_*`),
  default Colemak-DH, matching the cantor setup.
* Row offset is a single `#define` so `rows 2–4` can be tried instead of
  `rows 1–3` with a one-line change and a reflash.

## Toggle

* **Enter MIRYOKU**: HYPER layer active + `Shift` + `M` — handled in
  `process_record_user()`, then `set_single_persistent_default_layer(M_BASE)`.
* **Return to BASE**: the `BACK` key in MIRYOKU mode, `PDF(BASE)` (persistent,
  unlike `DF()`, which would only live until the next power cycle).
  (Same physical key as the HYPER key in BASE.)
* The choice persists across reboots (EEPROM), so `QK_CLEAR_EEPROM` matters.

## OLED

Three states, arbitrated in `oled_task_user()` (the port's own screens run
first and always win):

| State | Condition | Content |
| --- | --- | --- |
| Port screens | `menu_screen != OFF` | unchanged (menu, battery, confirm, help, hello) |
| Blank | `menu_screen == OFF`, idle ≥ 5 s | display off (the port's existing anti burn-in behaviour) |
| Idle art | `menu_screen == OFF`, awake | animation (bongo cat / luna frames) or, if frames fill the panel, the layout word |

* On every layout switch: a 2 s splash showing `BASE` or `MIRYOKU`.
* Layout word is shown whenever no other screen is up, so the active layout is
  never ambiguous.
* Animation frames come from QMK's in-tree bongo-cat keymaps
  (`keyboards/adpenrose/akemipad/keymaps/oled_bongocat/animation_frames.h`
  as a starting point) and must fit the port's 128×~32 panel.

## Host-controlled backlight

Stylix's backlight colour must keep working. MNT's stock firmware accepted
`xLRGB`/`xLBRT` output reports; QMK exposes a vendor raw HID endpoint instead,
so the module (`nixos-mnt-pocket-reform/modules/keyboard.nix`, matched on
`feed:0000`) sends one 32-byte output report, no report id:

```
byte 0  'C'
byte 1  red     0-255
byte 2  green   0-255
byte 3  blue    0-255
byte 4  value   0-255   (0 = backlight off)
bytes 5-31 unused
```

`pocket_backlight.c` receives it in `raw_hid_receive()`, converts RGB→HSV and
calls `rgblight_sethsv_noeeprom()`. The module writes the report to every
hidraw node of `feed:0000` because udev does not expose the HID usage page; only
the raw HID interface accepts it. The option's 0-150 brightness scale is
rescaled to 0-255 host-side, so the NixOS option keeps its stock semantics.

## Files

```
qmk-config/pocket-reform/keymap.c              layers (base, hyper, miryoku tables), toggle handler
qmk-config/pocket-reform/config.h              tapping term, row offset, alpha selection, backlight defaults
qmk-config/pocket-reform/pocket_reform.h       layer enum + layout-name accessors shared with the OLED code
qmk-config/pocket-reform/pocket_backlight.c    raw HID receiver for the host-set backlight colour
qmk-config/pocket-reform/rules.mk              RAW_ENABLE + extra sources
qmk-config/pocket-reform/oled_user.c           layout splashes + idle art
qmk-config/pocket-reform/readme.md             build + flash instructions, pinned port commit
qmk-config/install.sh                          new section: clone/pin the port, install keymap
qmk-config/README.md                           new device section
nixos-mnt-pocket-reform/modules/keyboard.nix   match feed:0000, send the QMK report
```

## Build & flash

```sh
# one-off
git clone https://codeberg.org/sleeplessval/qmk-pocket-reform <commit> \
  ~/qmk_firmware/keyboards/mntre/pocket_reform_hid
make mntre/pocket_reform_hid:dbeley

# loop
sudo picotool load mntre_pocket_reform_hid_dbeley.uf2 && sudo picotool reboot
```

Bootloader: menu → `X` (Hyper+Enter then X in BASE), or the boot keycode in
MIRYOKU's M_FUN layer, or the physical RESET button inside the top cover.

## Verification before "done"

- [ ] BASE: every key matches the table above; OLED menu opens on Hyper+Enter
- [ ] BASE: arrows reachable on HYPER; `MNT_SCRL` and mouse buttons still work
- [ ] Toggle: Hyper+Shift+M enters MIRYOKU; splash names the layout
- [ ] MIRYOKU: alphas/thumb layers behave as Miryoku; row 4 and columns 6–7 inert
- [ ] MIRYOKU: `BACK` returns to BASE; survives a power cycle
- [ ] Both: `QK_BOOT` and `QK_CLEAR_EEPROM` reachable; recovery via `picotool` works
- [ ] OLED: menu, battery, confirm, help still render; blanking still happens

## Open risks

1. **Thumb reach.** With alphas on rows 1–3 the home row is the physical QWER
   row, three rows above the thumb row. If that feels far, switch the row
   offset and reflash.
2. **Single-maintainer port.** If upstream stalls, the OLED/UART/trackball
   code is ours. Mitigation: pin the commit, keep the keymap dependency-free.
3. **Arm toolchain.** QMK on aarch64 needs `arm-none-eabi-gcc`; the version in
   nixpkgs (15.3) may trip QMK's warnings-as-errors. Fallback: pin an older
   `gcc-arm-embedded`, or use ARM's tarball in a devshell.
4. **Legend drift.** BASE's right-hand modifiers and MIRYOKU's alphas do not
   match the printed keycaps. All keys are 1u choc, so caps can be physically
   rearranged if wanted.
