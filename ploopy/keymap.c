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
#define PLOOPY_DRAGSCROLL_MULTIPLIER 0.1
#define PLOOPY_DRAGSCROLL_INVERT

/* enum custom_keycodes { */
/* 	NEXTTAB, */
/* 	PREVTAB */
/* }; */

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*     case PREVTAB: */
/*         if (record->event.pressed) { */
/*             // when keycode PREVTAB is pressed */
/*             register_code(KC_LCTL); */
/*             tap_code(KC_PGUP); */
/*             unregister_code(KC_LCTL); */
/*         } else { */
/*             // when keycode PREVTAB is released */
/*         } */
/*         break; */

/*     case NEXTTAB: */
/*         if (record->event.pressed) { */
/*             // when keycode NEXTTAB is pressed */
/*             register_code(KC_LCTL); */
/*             tap_code(KC_PGDN); */
/*             unregister_code(KC_LCTL); */
/*         } else { */
/*             // when keycode NEXTTAB is released */
/*         } */
/*         break; */
/*     } */
/*     return true; */
/* }; */

/*####################################################*/
/* Left-handed ploopy classic trackball               */
/*####################################################*/
/*                                                    */
/* Layout 0                                           */
/*                                                    */
/*                 .-------.     .---------.          */
/*    .---------. /         \   /      /    \         */
/*   /LAY2/LAY1/ (   BALL    ) /      /      \        */
/*   \    \    \  \         / /  .------.    |        */
/*    \    \    \  '-------' /  | BTN3  |   /         */
/*     \    \    \          /   '------'   /          */
/*      '--------'         / BTN1 / BTN2  /           */
/*                        '------'-------'            */
/*                                                    */
/*####################################################*/
/*                                                    */
/* Layout 1                                           */
/*                                                    */
/*                 .-------.     .---------.          */
/*    .---------. /         \   /      /    \         */
/*   /DPI /####/ (   BALL    ) /      /      \        */
/*   \    \    \  \         / /  .------.    |        */
/*    \    \    \  '-------' /  | DRSCR |   /         */
/*     \    \    \          /   '------'   /          */
/*      '--------'         / PGUP / PGDWN /           */
/*                        '------'-------'            */
/*                                                    */
/*####################################################*/
/*                                                    */
/* Layout 2                                           */
/*                                                    */
/*                 .-------.     .---------.          */
/*    .---------. /         \   /      /    \         */
/*   /####/DRSC/ (   BALL    ) /      /      \        */
/*   \    \    \  \         / /  .------.    |        */
/*    \    \    \  '-------' /  | DRSCR |   /         */
/*     \    \    \          /   '------'   /          */
/*      '--------'         / BTN3 / DRSCR /           */
/*                        '------'-------'            */
/*                                                    */
/*####################################################*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN2, KC_BTN3, KC_BTN1,
		LT(1, _______), LT(2, _______)
    ),
    [1] = LAYOUT(
        KC_PGDN, DRAG_SCROLL, KC_PGUP,
        _______, DPI_CONFIG
    ),
    [2] = LAYOUT(
        DRAG_SCROLL, DRAG_SCROLL, KC_BTN3,
        DRAG_SCROLL, _______
    )
};
