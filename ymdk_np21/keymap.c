#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY_GAMING,
    _QWERTY_GAMING_ALT,
    _QWERTY_GAMING2,
    _QWERTY_GAMING_ALT2,
    _NUM,
    _BL,
};

/* const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { */
/*     [_NP] = LAYOUT_ortho_6x4( */
/*         KC_ESC,  KC_TAB,  KC_BSPC, MO(_BL), */
/*         KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, */
/*         KC_P7,   KC_P8,   KC_P9,   KC_PPLS, */
/*         KC_P4,   KC_P5,   KC_P6,   KC_PPLS, */
/*         KC_P1,   KC_P2,   KC_P3,   KC_PENT, */
/*         KC_P0,   KC_DOT,  KC_PDOT, KC_PENT */
/*     ), */

/*     [_BL] = LAYOUT_ortho_6x4( */
/*         _______, _______, _______, _______, */
/*         _______, _______, _______, _______, */
/*         _______, BL_ON,   _______, BL_INC, */
/*         _______, BL_TOGG, _______, BL_INC, */
/*         _______, BL_OFF,  _______, BL_DEC, */
/*         BL_BRTG, _______, _______, BL_DEC */
/*     ) */
/* }; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY_GAMING] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        KC_LSFT, KC_LCTL, KC_U, KC_ESC,
        KC_SPC,  KC_Z,    KC_A, KC_Q,
        LT(_QWERTY_GAMING_ALT, KC_G),    KC_X,    KC_S, KC_W,
        KC_B,    KC_C,    KC_D, KC_E,
        KC_M,    KC_V,    KC_F, KC_R
        ),

[_QWERTY_GAMING_ALT] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        KC_0,     KC_H,   KC_6,   KC_1,
        KC_TAB,   KC_J,   KC_7,   KC_2,
        _______,  KC_K,   KC_8,   KC_3,
        KC_ENT,   KC_L,   KC_9,   KC_4,
        KC_N,     KC_I,   KC_T,   KC_5
        ),

[_QWERTY_GAMING2] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        KC_LSFT, KC_LCTL, KC_U, KC_ESC,
        KC_SPC,  KC_Z,    KC_LEFT, KC_Q,
        LT(_QWERTY_GAMING_ALT2, KC_G),    KC_X,    KC_DOWN, KC_UP,
        KC_B,    KC_C,    KC_RIGHT, KC_E,
        KC_M,    KC_V,    KC_F, KC_R
        ),

[_QWERTY_GAMING_ALT2] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        KC_0,     KC_H,   KC_6,   KC_1,
        KC_TAB,   KC_J,   KC_7,   KC_2,
        _______,  KC_K,   KC_8,   KC_3,
        KC_ENT,   KC_L,   KC_9,   KC_4,
        KC_N,     KC_I,   KC_T,   KC_5
        ),

[_NUM] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        KC_NUM,  KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PEQL,
        KC_P0,   BL_TOGG, KC_PDOT, KC_PENT
        ),
[_BL] = LAYOUT_ortho_6x4(
        DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_BL),
        _______, _______, _______, _______,
        _______, BL_ON,   _______, BL_UP,
        _______, BL_TOGG, _______, BL_UP,
        _______, BL_OFF,  _______, BL_DOWN,
        BL_BRTG, BL_STEP, _______, BL_DOWN
    	),

/* [_QWERTY] = LAYOUT_ortho_6x4( */
/*         DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_QWERTY), */
/*         LT(_QWERTY_MIRRORED, KC_SPC),    KC_Z, KC_A, KC_Q, */
/*         LSFT_T(KC_BSPC), KC_X, KC_S, KC_W, */
/*         LCTL_T(KC_TAB),  KC_C, KC_D, KC_E, */
/*         LALT_T(KC_ENT),  KC_V, KC_F, KC_R, */
/*         LGUI_T(KC_ESC),  KC_B, KC_G, KC_T */
/*         ), */

/* [_QWERTY_MIRRORED] = LAYOUT_ortho_6x4( */
/*         DF(_QWERTY_GAMING), DF(_QWERTY_GAMING2), DF(_NUM), DF(_QWERTY), */
/*         _______,         KC_N,    KC_H,    KC_Y, */
/*         LSFT_T(KC_DEL),  KC_M,    KC_J,    KC_U, */
/*         LCTL_T(KC_TAB),  KC_COMM, KC_K,    KC_I, */
/*         LALT_T(KC_ENT),  KC_DOT,  KC_L,    KC_O, */
/*         LGUI_T(KC_ESC),  KC_SLSH, KC_SCLN, KC_P */
/*         ), */

};
