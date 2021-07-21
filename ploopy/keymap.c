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
#define PLOOPY_DRAGSCROLL_MULTIPLIER 0.5
#define PLOOPY_DRAGSCROLL_INVERT

enum custom_keycodes {
	NEXTTAB,
	PREVTAB
}

/*####################################################*/
/* Left-handed ploopy classic trackball               */
/*####################################################*/
/*                                                    */
/* Layout 0                                           */
/*                                                    */
/*     .-------.      .-------.    .-----------.      */
/*    / \_ LAY1 \    /         \  /      /      \     */
/*   |    \_BTN3 \  |  BALL    | /      /        \    */
/*   \      \     \ \         / /   .------.     |    */
/*    \ LAY2 \     \-'-------'-/   | BTN3  |    /     */
/*     \ BTN5 \    /          /    '------'    /      */
/*      '-----'---'          /  BTN1 / BTN2   /       */
/*                          '-------'--------'        */
/*                                                    */
/*####################################################*/
/*                                                    */
/* Layout 1                                           */
/*                                                    */
/*     .-------.      .-------.    .-----------.      */
/*    / \_ #### \    /         \  /      /      \     */
/*   |    \_     \  |  BALL    | /      /        \    */
/*   \      \     \ \         / /   .------.     |    */
/*    \ DPI  \     \-'-------'-/   | DRSCR |    /     */
/*     \      \    /          /    '------'    /      */
/*      '-----'---'          /  PGUP / PGDWN  /       */
/*                          '-------'--------'        */
/*                                                    */
/*####################################################*/
/*                                                    */
/* Layout 2                                           */
/*                                                    */
/*     .-------.      .-------.    .-----------.      */
/*    / \_ DRSCR\    /         \  /      /      \     */
/*   |    \_     \  |  BALL    | /      /        \    */
/*   \      \     \ \         / /   .------.     |    */
/*    \ #### \     \-'-------'-/   | DRSCR |    /     */
/*     \      \    /          /    '------'    /      */
/*      '-----'---'          / NXTAB / PRTAB  /       */
/*                          '-------'--------'        */
/*                                                    */
/*####################################################*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN2, KC_BTN3, KC_BTN1,
		LT(1, KC_BTN3), LT(2, KC_BTN5)
    ),
    [1] = LAYOUT(
        KC_PGDN, DRAG_SCROLL, KC_PGUP,
        _______, DPI_CONFIG
    ),
    [2] = LAYOUT(
        NEXTTAB, DRAG_SCROLL, PREVTAB,
        DRAG_SCROLL, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case NEXTTAB:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_TAB)SS_UP(X_LCTL));
        } else {
            // when keycode QMKURL is released
        }
    case PREVTAB:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LSFT)SS_TAP(X_TAB)SS_UP(X_LSFT)SS_UP(X_LCTL));
        } else {
            // when keycode QMKURL is released
        }
        break;
    }
    return true;
};
