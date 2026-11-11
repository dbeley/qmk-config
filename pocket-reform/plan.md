# Pocket Reform two-layout QMK firmware — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Ship a QMK firmware for the MNT Pocket Reform whose BASE layer has right-hand modifiers and whose MIRYOKU layout can be toggled at runtime from the keyboard.

**Architecture:** The community QMK port `mntre/pocket_reform_hid` provides the hardware (RP2040, OLED, trackball, UART to the system controller). We add nothing to the port; all our code lives in one keymap directory, `keymaps/dbeley/`, holding the layer tables (`keymap.c`), tuning (`config.h`), shared layer enum (`pocket_reform.h`) and OLED extras (`oled_user.c`). The two layouts are two parallel layer chains selected with `set_single_persistent_default_layer()`.

**Tech Stack:** QMK (RP2040, `gcc-arm-embedded`), `picotool` for flashing, Nix for the toolchain, `sh` for `install.sh`.

**Spec:** `pocket-reform/design.md` (same repo) — read it alongside this plan.

## Global Constraints

- Do not modify the port's own files (`config.h`, `rules.mk`, `oled.c`, `pocket_reform_hid.c`, `trackball.c`) — only files inside `keymaps/dbeley/`.
- `TAPPING_TERM 200` (matches the cantor setup) and `PERMISSIVE_HOLD` for home-row mods.
- Miryoku alpha default: Colemak-DH (`MIRYOKU_ALPHAS_COLEMAKDH`).
- Every keymap must keep a bootloader path reachable: `QK_BOOT` in the HYPER layer and in MIRYOKU's `_M_FUN`; `QK_CLEAR_EEPROM` in `_M_FUN`.
- The four small thumb keys stay `MS_BTN3`, `MS_BTN1`, `MNT_SCRL`, `MS_BTN2` in every layer.
- `LAYOUT` takes exactly 64 arguments: 5 rows × 12 keys, then `MS_BTN3, MS_BTN1, MNT_SCRL, MS_BTN2`.
- No unit tests exist for firmware. The gate for every task is: `qmk lint` clean → compiles → the task's on-device checklist passes. Never flash a keymap that removes the only boot path on the device.
- Commit messages in this repo are short and imperative (`pocket-reform: add base layer keymap`).

## Review Focus

1. **Losing the boot path.** A keymap whose only route to the bootloader is a key that MIRYOKU mode removed leaves the laptop recoverable only by opening the top cover. Expect both layouts to expose `QK_BOOT` (Task 3).
2. **Stale EEPROM default layer.** `set_single_persistent_default_layer()` survives reboots; flashing a keymap where MIRYOKU's `BACK` key moved strands the user in MIRYOKU. Expect `BACK` and `QK_CLEAR_EEPROM` in the same commit as the toggle (Task 3).
3. **OLED task collision.** QMK's `oled_task_user()` runs after the port's own screen code; drawing over a menu/confirm screen makes power-off hangs possible. Expect art and indicator to be suppressed whenever `menu_screen != OFF` (Tasks 4, 5).
4. **Dead keys that are not dead.** Column/row mistakes in the MIRYOKU block leave live keys or kill an intended one. Expect every position listed as inert in the spec to be pressed and observed as a no-op (Task 3).
5. **Home-row mod mis-taps.** With `TAPPING_TERM 200`, fast rolls can register as mods. Expect a quick-typing sanity pass before the task is called done (Task 3).

---

### Task 1: Toolchain, port installed, stock QMK running on the device

De-risks everything else: prove we can build and flash before writing any keymap.

**Files:**
- Create: `pocket-reform/readme.md` (setup notes + the qmk_firmware commit used)

**Interfaces:**
- Produces: a working `~/src/qmk_firmware` tree with `keyboards/mntre/pocket_reform_hid` installed, and a repeatable build/flash loop used by every later task.

- [ ] **Step 1: Install the QMK tree and the port**

```sh
mkdir -p ~/src && cd ~/src
git clone https://github.com/qmk/qmk_firmware.git
git clone https://codeberg.org/sleeplessval/qmk-pocket-reform.git
git -C qmk-pocket-reform checkout 75057bb26ff4cdb6744a5c7e0db87a2fc8f8228c
# upstream ships keyboards/mntre (classic Reform); move it out of the build tree
mkdir -p ~/src/disabled-mntre && mv qmk_firmware/keyboards/mntre/* ~/src/disabled-mntre/
cp -r qmk-pocket-reform qmk_firmware/keyboards/mntre/pocket_reform_hid
```

- [ ] **Step 2: Enter the toolchain shell**

```sh
nix shell nixpkgs#qmk nixpkgs#gcc-arm-embedded nixpkgs#picotool nixpkgs#git
```

- [ ] **Step 3: Build the port's stock keymap**

Run: `cd ~/src/qmk_firmware && qmk compile -kb mntre/pocket_reform_hid -km default`
Expected: `mntre_pocket_reform_hid_default.uf2` in `~/src/qmk_firmware`. If the nix `qmk` CLI refuses to use an external `QMK_HOME`, fall back to `make mntre/pocket_reform_hid:default` with `python3` added to the nix shell, and record which route worked in `readme.md`.

- [ ] **Step 4: Flash it on the pocket**

Copy the `.uf2` to the pocket, open the menu (Hyper+Enter), press `X`, confirm, then:

```sh
nix shell nixpkgs#picotool
sudo picotool load mntre_pocket_reform_hid_default.uf2 && sudo picotool reboot
```

- [ ] **Step 5: Verify on device**

Checklist: typing works; trackball moves and clicks; `MNT_SCRL` toggles scrolling; OLED shows the hello/battery/menu screens; Hyper+Enter menu power actions still listed.

- [ ] **Step 6: Commit**

```sh
cd ~/Documents/qmk-config
git add pocket-reform/readme.md
git commit -m "pocket-reform: document qmk setup and port pin"
```

---

### Task 2: BASE layer — right-hand modifiers, arrows on HYPER

**Files:**
- Create: `pocket-reform/pocket_reform.h`, `pocket-reform/config.h`, `pocket-reform/keymap.c`
- Modify: `pocket-reform/readme.md` (install line for the keymap)

**Interfaces:**
- Produces: `enum pocket_layers { _BASE, _HYPER, ... POCKET_LAYER_COUNT }` in `pocket_reform.h`; `bool pocket_is_miryoku(void)` and `const char *pocket_layout_name(void)` implemented in `keymap.c` (`"BASE"` / `"MIRYOKU"`).

- [ ] **Step 1: Write `pocket_reform.h`**

```c
#pragma once
#include QMK_KEYBOARD_H

enum pocket_layers {
    _BASE, _HYPER,
    POCKET_LAYER_COUNT
};

bool pocket_is_miryoku(void);
const char *pocket_layout_name(void);
```

- [ ] **Step 2: Write `config.h`**

Only `#define TAPPING_TERM 200` and `#define PERMISSIVE_HOLD` for now (home-row mods arrive in Task 3).

- [ ] **Step 3: Write `keymap.c` with two layers**

Copy the port's `keymaps/default/keymap.c` as the starting point, then apply the spec's BASE table: row 4 becomes `…, KC_UP, KC_RSFT` (was `KC_RALT`), row 5 becomes `MO(_HYPER), KC_LGUI, KC_LALT, KC_BSLS, KC_EQL, KC_SPC, KC_SPC, KC_MINS, KC_SLSH, KC_RALT, KC_DOWN, KC_RCTL`. In HYPER, keep the port's table but add `KC_LEFT/KC_DOWN/KC_UP/KC_RIGHT` on `H/J/K/L`, give `KC_UP` back `KC_PGUP`, and put `QK_BOOT` in the `KC_F13` slot (row 2, column 4) as the backup bootloader route. Implement `pocket_is_miryoku()` as `return false;` (stub, extended in Task 3) and `pocket_layout_name()` returning `"BASE"` when it is false.

- [ ] **Step 4: Lint and build**

Run: `qmk lint -kb mntre/pocket_reform_hid -km dbeley` then `qmk compile -kb mntre/pocket_reform_hid -km dbeley`
Expected: no errors, `mntre_pocket_reform_hid_dbeley.uf2` produced. An arity error here means the `LAYOUT` argument count is not 64.

- [ ] **Step 5: Flash and verify**

Flash per Task 1 Step 4. On-device: `RAlt` position acts as Shift; `←`/`↓`/`→` positions act as AltGr/Meta/Ctrl; `↑` still moves up; HYPER+`H/J/K/L` move the cursor; HYPER+Enter opens the menu; `AltGr`-combinations for accented characters still work.

- [ ] **Step 6: Commit**

```sh
git add pocket-reform/
git commit -m "pocket-reform: base layer with right-hand modifiers"
```

---

### Task 3: MIRYOKU layers and the runtime toggle

**Files:**
- Modify: `pocket-reform/keymap.c`, `pocket-reform/pocket_reform.h`, `pocket-reform/config.h`

**Interfaces:**
- Consumes: `_BASE`, `_HYPER`, `pocket_is_miryoku()`, `pocket_layout_name()` from Task 2.
- Produces: layers `_M_BASE, _M_EXTRA, _M_TAP, _M_BUTTON, _M_NAV, _M_MOUSE, _M_MEDIA, _M_NUM, _M_SYM, _M_FUN`; `pocket_layout_name()` now returns `"MIRYOKU"` when the default layer is `_M_BASE`.

- [ ] **Step 1: Fetch the Miryoku tables**

```sh
cd ~/src && curl -sSLo /tmp/alt.h \
  https://raw.githubusercontent.com/manna-harbour/miryoku_qmk/miryoku/users/manna-harbour_miryoku/miryoku_babel/miryoku_layer_alternatives.h
grep -n '^#define MIRYOKU_ALTERNATIVES_' /tmp/alt.h
```

Take `BASE_COLEMAKDH` plus the non-alternative `TAP, BUTTON, NAV, MOUSE, MEDIA, NUM, SYM, FUN` tables (and `EXTRA` if present) and paste them into `keymap.c` as `static const uint16_t PROGMEM miryoku_<layer>[4][10]`-shaped comments — keep them as macros next to the keymap so the mapping stays readable and re-pasteable. Record the miryoku commit/date in a comment.

- [ ] **Step 2: Add the layer enum and key aliases**

Extend `pocket_reform.h` with the ten `_M_*` layers. In `keymap.c` add:

```c
#define U_NA           KC_NO
#define U_NP           KC_NO
#define U_BASE         _M_BASE
#define U_EXTRA        _M_EXTRA
#define U_TAP          _M_TAP
#define U_BUTTON       _M_BUTTON
#define U_NAV          _M_NAV
#define U_MOUSE        _M_MOUSE
#define U_MEDIA        _M_MEDIA
#define U_NUM          _M_NUM
#define U_SYM          _M_SYM
#define U_FUN          _M_FUN
```

Replace every `U_TD_*` / `TD(...)` from the pasted tables with `U_NA`.

- [ ] **Step 3: Write the ten MIRYOKU layers**

Each layer is `LAYOUT(...)` with 5 rows of 12: Miryoku's per-hand rows go to columns 1-5 and 8-12, `U_NP` in columns 6-7; row 5 is 12 entries with `U_NP, U_NP`, the six thumb entries in columns 3-8, then `U_NP` ×4; row 4 is twelve `U_NP`; the four thumb-key arguments stay `MS_BTN3, MS_BTN1, MNT_SCRL, MS_BTN2`. Replace `_M_BASE`'s column 1 of row 5 with `DF(_BASE)` (the `BACK` key), and add `QK_BOOT` + `QK_CLEAR_EEPROM` to `_M_FUN` in place of two `U_NA`s.

Keep the dead row obvious and movable: the inert filler row is the row of twelve `U_NP` (row 4 by default). Switching to "alphas on rows 2-4" is then a matter of moving that filler row to index 0 and shifting the three alpha rows down one — note the two-line edit in `readme.md`.

- [ ] **Step 4: Add the toggle handler**

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_M &&
        layer_state_is(_HYPER) && (get_mods() & MOD_MASK_SHIFT)) {
        set_single_persistent_default_layer(_M_BASE);
        layer_clear();
        return false;
    }
    return true;
}
```

- [ ] **Step 5: Lint and build**

Run: `qmk lint -kb mntre/pocket_reform_hid -km dbeley && qmk compile -kb mntre/pocket_reform_hid -km dbeley`
Expected: clean, `.uf2` produced.

- [ ] **Step 6: Flash and verify**

On-device: Hyper+Shift+M switches layout; Colemak-DH alphas with home-row mods on the QWER row; the six thumb keys reach Fun/Num/Sym and Mouse/Nav/Media; **every** key of row 4 and columns 6-7 of rows 1-3 is a no-op; `BACK` (bottom-left) returns to BASE; after a power cycle the layout is whichever was last selected; `QK_CLEAR_EEPROM` in `_M_FUN` returns the keyboard to BASE; `QK_BOOT` in `_M_FUN` still reaches the bootloader.

- [ ] **Step 7: Commit**

```sh
git add pocket-reform/
git commit -m "pocket-reform: miryoku layout with runtime toggle"
```

---

### Task 4: OLED layout indicator and switch splash

**Files:**
- Create: `pocket-reform/oled_user.c`
- Modify: none expected — QMK compiles every `*.c` in the keymap directory.

**Interfaces:**
- Consumes: `pocket_layout_name()` from Task 2/3, `menu_screen` from `oled.h`.

- [ ] **Step 1: Write `oled.c`-safe rendering**

`void oled_task_user(void)` in `oled_user.c`: `if (menu_screen != OFF) return;` then draw `pocket_layout_name()` on the last text line. Keep a `static char last[16]`; when the name changes, start a 2000 ms `splash_timer` during which the name is drawn large/centered instead.

- [ ] **Step 2: Build**

Run: `qmk compile -kb mntre/pocket_reform_hid -km dbeley`
Expected: clean compile; a link error mentioning `oled_task_user` duplicated means the port's `oled.c` already defines it — in that case delegate from the keymap instead and record the decision in `readme.md`.

- [ ] **Step 3: Flash and verify**

On-device: `BASE` shown when idle in BASE and `MIRYOKU` in MIRYOKU; switching layouts shows the 2 s splash; menu, battery, confirm and help screens still render and still blank after 5 s idle.

- [ ] **Step 4: Commit**

```sh
git add pocket-reform/
git commit -m "pocket-reform: oled layout indicator"
```

---

### Task 5: Idle art (bongo cat), optional

**Files:**
- Create: `pocket-reform/art.h` (frame arrays)
- Modify: `pocket-reform/oled_user.c`

- [ ] **Step 1: Measure the panel**

Temporarily draw a 128×64 border box in `oled_task_user()`; flash and observe which rows are visible. Record the panel height in `readme.md`. Expected: 128×32 (rows 32-63 invisible).

- [ ] **Step 2: Choose or crop frames to that height**

Start from QMK's in-tree bongo-cat frames (`keyboards/adpenrose/akemipad/keymaps/oled_bongocat/animation_frames.h`) and crop/downsample to the measured height; ASCII-art frames drawn with `oled_write_P` are equally acceptable and much smaller.

- [ ] **Step 3: Render art only when nothing else is on screen**

In `oled_task_user()`, when `menu_screen == OFF` and the layout name is not splashing, draw the current frame (advance on a timer). Leave the port's 5 s blanking untouched.

- [ ] **Step 4: Build, flash, verify**

Art appears while typing and while idle-but-awake, disappears with the 5 s blank, never appears over a menu/confirm screen, and the layout name is still legible (or returns immediately after input).

- [ ] **Step 5: Commit**

```sh
git add pocket-reform/
git commit -m "pocket-reform: idle oled art"
```

---

### Task 6: Repo integration — `install.sh`, README, pins

**Files:**
- Modify: `install.sh`, `README.md`

- [ ] **Step 1: Add the pocket section to `install.sh`**

Mirror the existing devices: clone the port at the pinned commit into a temp dir, move upstream `keyboards/mntre/*` aside, copy the port to `keyboards/mntre/pocket_reform_hid`, then `mkdir -p keymaps/dbeley` and copy `pocket-reform/*.c pocket-reform/*.h` into it. Leave a commented `# qmk compile -kb mntre/pocket_reform_hid -km dbeley`.

- [ ] **Step 2: Add the README section**

Device entry in the list, the bootloader routes (menu `X`, `QK_BOOT` in HYPER and `_M_FUN`, hardware RESET under the top cover), the build/flash commands, the layout switch shortcut (Hyper+Shift+M, `BACK` to return), the pinned port commit, and the qmk_firmware commit used.

- [ ] **Step 3: Verify the script on a clean clone**

Run the pocket section of `install.sh` against a fresh `qmk_firmware` clone; expect the port installed and `qmk compile -kb mntre/pocket_reform_hid -km dbeley` to succeed afterwards.

- [ ] **Step 4: Commit**

```sh
git add install.sh README.md
git commit -m "pocket-reform: install script and docs"
```

---

### Task 7: Host-controlled backlight colour (QMK raw HID)

Keeps stylix's backlight colour working after leaving MNT's firmware. Two repos,
one protocol; the spec lives in `design.md` ("Host-controlled backlight").

**Files:**
- Create: `pocket-reform/pocket_backlight.c`, `pocket-reform/rules.mk`
- Modify: `~/Documents/nixos-mnt-pocket-reform/modules/keyboard.nix`

- [ ] **Step 1: Receive the report in the keymap**

`pocket_backlight.c` implements `void raw_hid_receive(uint8_t *data, uint8_t length)`:
ignore anything shorter than 5 bytes or whose `data[0]` is not `'C'`; convert
`data[1..3]` to HSV with a local `rgb_to_hue8()` (QMK only ships hsv→rgb); if
`data[4]` is 0 call `rgblight_disable_noeeprom()`, otherwise
`rgblight_enable_noeeprom()` + `rgblight_sethsv_noeeprom(hue, sat, data[4])`.
`rules.mk` sets `RAW_ENABLE = yes` and `SRC += pocket_backlight.c`.

- [ ] **Step 2: Build and confirm the endpoint exists**

Run: `qmk compile -kb mntre/pocket_reform_hid -km dbeley && nm .build/mntre_pocket_reform_hid_dbeley.elf | grep raw_hid`
Expected: `raw_hid_receive`, `raw_hid_task`, `send_raw_hid` present, and the USB
descriptor contains usage page `0xFF60`.

- [ ] **Step 3: Flash, then count the hidraw nodes**

After flashing, run: `grep -l FEED /sys/class/hidraw/hidraw*/device/uevent | wc -l`
Expected: 3 (keyboard, mouse, raw HID) instead of 2.

- [ ] **Step 4: Send the frame by hand before touching the module**

```sh
printf '\x43\x8F\x88\xD5\x44\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' > /dev/hidrawN
```
(`N` = the node that accepts it; the other two return `EINVAL`.)
Expected: backlight turns purple at ~27 % brightness.

- [ ] **Step 5: Re-teach the NixOS module**

`modules/keyboard.nix`: match `idVendor=="feed", idProduct=="0000"`; build the
32-byte report in Nix (`[ 67 r g b (brightness * 255 / 150) ] ++ replicate 27 0`,
rendered as `\xNN` escapes so bash's `printf` emits NULs correctly); write it to
every matching hidraw node, ignoring `EINVAL`; keep sending on every
(re)enumeration.

- [ ] **Step 6: Verify through the module**

`nixos-rebuild switch` (after bumping the flake input), replug or resume:
Expected: the keyboard comes back in the stylix colour without any keypress.
