/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define PLOOPY_DPI_OPTIONS { 400, 800, 1200, 1600, 2000, 2400 }
#define PLOOPY_DPI_DEFAULT 1
// safe range starts at `PLOOPY_SAFE_RANGE` instead.

// Tap Dance declarations
enum {
  TD_NAV
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Escape, twice for Caps Lock
  /* [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS), */
  [TD_NAV] = ACTION_TAP_DANCE_DOUBLE(KC_WBAK, KC_WFWD)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* [0] = LAYOUT( /1* Base *1/ */
    /*     KC_BTN1, KC_BTN3, KC_BTN2, */
    /*       KC_BTN4, KC_BTN5 */
    /* ), */
    [0] = LAYOUT( /* Base */
        KC_BTN2, KC_BTN3, KC_BTN1,
		TD(TD_NAV), LT(1, KC_BTN5)
    ),
    [1] = LAYOUT(
        KC_PGDN, DRAG_SCROLL, KC_PGUP,
          DPI_CONFIG, _______
    )
};
