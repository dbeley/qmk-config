// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Home-row mods arrive with the Miryoku layers (see plan.md, task 3); QMK's
// default 200 ms term is what the cantor setup uses, so keep them in sync.
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// Resolve tap-hold keys by hand, not by clock: a second key on the same hand
// makes the first one a tap (typing rolls), a second key on the other hand makes
// it a hold (mods, layer thumbs). Needs chordal_hold_layout in keymap.c.
#define CHORDAL_HOLD

// A tap-hold key pressed right after a letter is settled as a tap immediately,
// which both avoids stray mods and removes the tap latency while typing fast.
// The layer thumbs are exempted in get_flow_tap_term() in keymap.c.
#define FLOW_TAP_TERM 150

// The port's config.h boots the RGB backlight off (RGBLIGHT_DEFAULT_ON false),
// which leaves the keyboard dark. Turn it back on, matching the brightness the
// stock firmware used. NOTE: rgb state lives in EEPROM, so an already-booted
// keyboard needs one RGB_TOG press (HYPER + \) or QK_CLEAR_EEPROM to pick this
// up.
#undef RGBLIGHT_DEFAULT_ON
#define RGBLIGHT_DEFAULT_ON true
