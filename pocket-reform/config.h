// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Home-row mods arrive with the Miryoku layers (see plan.md, task 3); QMK's
// default 200 ms term is what the cantor setup uses, so keep them in sync.
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// The port's config.h boots the RGB backlight off (RGBLIGHT_DEFAULT_ON false),
// which leaves the keyboard dark. Turn it back on, matching the brightness the
// stock firmware used. NOTE: rgb state lives in EEPROM, so an already-booted
// keyboard needs one RGB_TOG press (HYPER + \) or QK_CLEAR_EEPROM to pick this
// up.
#undef RGBLIGHT_DEFAULT_ON
#define RGBLIGHT_DEFAULT_ON true
