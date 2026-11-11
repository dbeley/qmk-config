// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "pocket_reform.h"

bool pocket_is_miryoku(void) {
    // Miryoku layers land in task 3; until then BASE is always the default.
    return false;
}

const char *pocket_layout_name(void) {
    return pocket_is_miryoku() ? "MIRYOKU" : "BASE";
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * BASE: the stock layout, with modifiers added on the right side.
     * RALT is RShift; the old arrow cluster is AltGr / Meta / Ctrl.
     * Arrows live on the HYPER layer (HJKL). Two space keys kept as-is.
     *
     * ┌─────┬─────┬─────┬───┬───┬───┬───┬───┬───┬───┬───┬──────┐
     * │ ESC │  1  │  2  │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ BSPC │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼───┼──────┤
     * │ TAB │  Q  │  W  │ E │ R │ T │ Y │ U │ I │ O │ P │ ;    │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼───┼──────┤
     * │ CTL │  A  │  S  │ D │ F │ G │ H │ J │ K │ L │ ' │ ENT  │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼───┼──────┤
     * │ SFT │  Z  │  X  │ C │ V │ B │ N │ M │ , │ . │ ↑ │ RSFT │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼───┼──────┤
     * │ MO  │ GUI │ ALT │ \ │ = │   │   │ - │ / │RALT │RGI │ RCTL │
     * └─────┴─────┴─────┼───┼───┼───┴───┼───┼───┼───┴───┴──────┘
     *                   │ M3│ M1│       │SCR│ M2│
     *                   └───┴───┘       └───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_BSPC,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_SCLN,
        KC_LCTL,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_QUOT,     KC_ENT,
        KC_LSFT,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_UP,       KC_RSFT,
        MO(_HYPER),  KC_LGUI,     KC_LALT,     KC_BSLS,     KC_EQL,      KC_SPC,      KC_SPC,      KC_MINS,     KC_SLSH,     KC_RALT,     KC_RGUI,     KC_RCTL,
        MS_BTN3,     MS_BTN1,                                                                                    MNT_SCRL,    MS_BTN2
    ),
    /*
     * HYPER: functions on the number row, arrows on HJKL, OLED menu on Enter,
     * RGB controls and the bootloader escape on the bottom row.
     *
     * ┌─────┬─────┬─────┬───┬───┬───┬───┬───┬───┬───┬─────┬──────┐
     * │  `  │ F1  │ F2  │F3 │F4 │F5 │F6 │F7 │F8 │F9 │ F10 │ BSPC │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼─────┼──────┤
     * │     │ F11 │ F12 │F13│   │   │   │   │ I │ [ │ ]   │      │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼─────┼──────┤
     * │     │     │     │   │   │   │ ← │ ↓ │ ↑ │ → │     │ MENU │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼─────┼──────┤
     * │     │     │     │   │   │   │   │   │   │   │ PGUP│ RSFT │
     * ├─────┼─────┼─────┼───┼───┼───┼───┼───┼───┼───┼─────┼──────┤
     * │     │     │     │RGB│VAL+│  │   │VAL-│   │     │     │ BOOT │
     * └─────┴─────┴─────┼───┼───┼───┴───┼───┼───┴───┴─────┴──────┘
     *                   │   │   │       │   │
     *                   └───┴───┘       └───┘
     */
    [_HYPER] = LAYOUT(
        KC_GRV,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_BSPC,
        KC_TRNS,     KC_F11,      KC_F12,      KC_F13,      KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_I,        KC_LBRC,     KC_RBRC,     KC_TRNS,
        KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT,     KC_TRNS,     MNT_MENU,
        KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_PGUP,     KC_RSFT,
        KC_TRNS,     KC_TRNS,     KC_TRNS,     UG_TOGG,     UG_VALU,     KC_TRNS,     KC_TRNS,     UG_VALD,     KC_TRNS,     KC_TRNS,     KC_TRNS,     QK_BOOT,
        KC_TRNS,     KC_TRNS,                                                                                    KC_TRNS,     KC_TRNS
    )
};
