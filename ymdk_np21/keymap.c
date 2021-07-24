#include QMK_KEYBOARD_H
#include "artsey.h"
#include "keymap_combo.h"
#include "artsey.c"

/* enum layer_names { */
/*     _NP, */
/*     _BL */
/* }; */

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

 /* Learn more about the Artsey layout at https://artsey.io */

/* Base Layer
 *  Left-hand side   | Righ-hand side
 * .-----------------------------------.
 * |        |        |        |        |
 * |--------+--------+--------+--------|
 * .-----------------------------------.
 * .-----------------------------------.
 * | O      | S      | S      | O      |
 * |--------+--------+--------+--------|
 * | I      | T      | T      | I      |
 * |--------+--------+--------+--------|
 * | Y      | R      | R      | Y      |
 * |--------+--------+--------+--------|
 * | E      | A      | A      | E      |
 * |--------+--------+--------+--------|
 * | SFT    | BCKSP  | ENTER  | SPC    |
 * '-----------------------------------'
 */
[_FROG] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        LT(_FROG_ALT,KC_SPC),  KC_U, KC_O, KC_F,
        LSFT_T(KC_ESC),        KC_I, KC_E, KC_A,
        LCTL_T(KC_TAB),        KC_N, KC_H, KC_R,
        LALT_T(KC_BSPC),       KC_S, KC_T, KC_W,
        LGUI_T(KC_ENT),        KC_Y, KC_D, KC_P
        ),

[_FROG_ALT] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        _______,         _______, KC_Q, _______,
        LSFT_T(KC_BSPC), _______, KC_Z, _______,
        LCTL_T(KC_DEL),  KC_K, KC_L, KC_B,
        LALT_T(KC_SPC),  KC_G, KC_C, KC_M,
        LGUI_T(KC_SPC),  KC_X, KC_V, KC_J
        ),

[_NUM] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        KC_NLCK, KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PEQL,
        KC_P0,   KC_PCMM, KC_PDOT, KC_PENT
        ),

/* [_QWERTY] = LAYOUT_ortho_6x4( */
/*         DF(_A_BASE), DF(FROG), DF(NUM), DF(QWERTY), */
/*         KC_1,    KC_2, KC_3, KC_4, */
/*         KC_ESC,  KC_Q, KC_W, KC_E, */
/*         KC_LSFT, KC_A, KC_S, KC_D, */
/*         KC_LCTL, KC_Z, KC_X, KC_C, */
/*         KC_SPC,  KC_R, KC_F, KC_V */
/*         ), */
[_QWERTY] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        LT(_QWERTY_MIRRORED, KC_ESC),    KC_Z, KC_A, KC_Q,
        LSFT_T(KC_ESC),  KC_X, KC_S, KC_W,
        LCTL_T(KC_TAB),  KC_C, KC_D, KC_E,
        LALT_T(KC_BSPC), KC_V, KC_F, KC_R,
        LGUI_T(KC_ENT),  KC_B, KC_G, KC_T
        ),

[_QWERTY_MIRRORED] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        _______,         KC_N,    KC_H,    KC_Y,
        LSFT_T(KC_BSPC), KC_M,    KC_J,    KC_U,
        LCTL_T(KC_DEL),  KC_COMM, KC_K,    KC_I,
        LALT_T(KC_SPC),  KC_DOT,  KC_L,    KC_O,
        LGUI_T(KC_SPC),  KC_SLSH, KC_SCLN, KC_P
        ),

[_A_BASE] = LAYOUT_ortho_6x4(
        DF(_A_BASE), DF(_FROG), DF(_NUM), DF(_QWERTY),
        A_BASE_O, A_BASE_S, A_BASE_S, A_BASE_O,
        A_BASE_I, A_BASE_T, A_BASE_T, A_BASE_I,
        A_BASE_Y, A_BASE_R, A_BASE_R, A_BASE_Y,
        A_BASE_E, A_BASE_A, A_BASE_A, A_BASE_E,
        LSFT_T(KC_ESC), KC_BSPC, KC_ENT, KC_SPC
        ),

[_A_NUM] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_NUM_O, A_NUM_S, A_NUM_S, A_NUM_O,
        A_NUM_I, A_NUM_T, A_NUM_T, A_NUM_I,
        A_NUM_Y, A_NUM_R, A_NUM_R, A_NUM_Y,
        A_NUM_E, A_NUM_A, A_NUM_A, A_NUM_E,
        _______, _______, _______, _______
        ),

[_A_NAV] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_NAV_O, A_NAV_S, A_NAV_S, A_NAV_O,
        A_NAV_I, A_NAV_T, A_NAV_T, A_NAV_I,
        A_NAV_Y, A_NAV_R, A_NAV_R, A_NAV_Y,
        A_NAV_E, A_NAV_A, A_NAV_A, A_NAV_E,
        _______, _______, _______, _______
        ),

[_A_SYM] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_SYM_O, A_SYM_S, A_SYM_S, A_SYM_O,
        A_SYM_I, A_SYM_T, A_SYM_T, A_SYM_I,
        A_SYM_Y, A_SYM_R, A_SYM_R, A_SYM_Y,
        A_SYM_E, A_SYM_A, A_SYM_A, A_SYM_E,
        _______, _______, _______, _______
        ),

[_A_BRAC] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_BRAC_O, A_BRAC_S, A_BRAC_S, A_BRAC_O,
        A_BRAC_I, A_BRAC_T, A_BRAC_T, A_BRAC_I,
        A_BRAC_Y, A_BRAC_R, A_BRAC_R, A_BRAC_Y,
        A_BRAC_E, A_BRAC_A, A_BRAC_A, A_BRAC_E,
        _______, _______, _______, _______
        ),

[_A_MOU] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_MOU_O, A_MOU_S, A_MOU_S, A_MOU_O,
        A_MOU_I, A_MOU_T, A_MOU_T, A_MOU_I,
        A_MOU_Y, A_MOU_R, A_MOU_R, A_MOU_Y,
        A_MOU_E, A_MOU_A, A_MOU_A, A_MOU_E,
        _______, _______, _______, _______
        ),

[_A_CUSTOM] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        A_CUSTOM_O, A_CUSTOM_S, A_CUSTOM_S, A_CUSTOM_O,
        A_CUSTOM_I, A_CUSTOM_T, A_CUSTOM_T, A_CUSTOM_I,
        A_CUSTOM_Y, A_CUSTOM_R, A_CUSTOM_R, A_CUSTOM_Y,
        A_CUSTOM_E, A_CUSTOM_A, A_CUSTOM_A, A_CUSTOM_E,
        _______, _______, _______, _______
        )


};
