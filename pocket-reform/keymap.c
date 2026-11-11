// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "pocket_reform.h"

bool pocket_is_miryoku(void) {
    return get_highest_layer(default_layer_state) >= _M_BASE;
}

const char *pocket_layout_name(void) {
    return pocket_is_miryoku() ? "MIRYOKU" : "BASE";
}

/* ---------------------------------------------------------------- miryoku --
 *
 * Layer tables copied verbatim from miryoku_qmk (Colemak-DH alphas, VI
 * navigation, mirroring the cantor setup): users/manna-harbour_miryoku/
 * miryoku_babel/miryoku_layer_alternatives.h
 *
 * Two substitutions only:
 *   - Miryoku's tap-dance boot/tap/extra keys become U_NA (we do not carry the
 *     TAP layer; QK_BOOT and QK_CLEAR_EEPROM sit on _M_FUN instead).
 *   - RGB_* keycodes use their current QMK names (UG_*), and OU_AUTO is dropped.
 *
 * Miryoku rows are 10 keys wide (5 per hand). LAYOUT_MIRYOKU spreads them over
 * the pocket's 12-column rows, leaves columns 6-7 of the alpha rows and the
 * whole 4th row inert, and puts Miryoku's six thumbs on the 5th row.
 */

#define U_NA KC_NO
#define U_NP KC_NO
#define U_NU KC_NUM
// Clipboard keys: Miryoku's U_* names are gone from current QMK.
#define U_UND KC_UNDO
#define U_CUT KC_CUT
#define U_CPY KC_COPY
#define U_PST KC_PASTE
#define U_RDO KC_AGAIN
// Mouse keys: current QMK spells them MS_*, Miryoku's tables use KC_*.
#define KC_MS_L MS_LEFT
#define KC_MS_D MS_DOWN
#define KC_MS_U MS_UP
#define KC_MS_R MS_RGHT
#define KC_WH_L MS_WHLL
#define KC_WH_D MS_WHLD
#define KC_WH_U MS_WHLU
#define KC_WH_R MS_WHLR
#define KC_BTN1 MS_BTN1
#define KC_BTN2 MS_BTN2
#define KC_BTN3 MS_BTN3
#define U_BASE _M_BASE
#define U_BUTTON _M_BUTTON
#define U_NAV _M_NAV
#define U_MOUSE _M_MOUSE
#define U_MEDIA _M_MEDIA
#define U_NUM _M_NUM
#define U_SYM _M_SYM
#define U_FUN _M_FUN

#define DEAD_ROW U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP, U_NP

// alpha rows: 5 keys, gap, 5 keys
#define RM10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) a1, a2, a3, a4, a5, U_NP, U_NP, a6, a7, a8, a9, a10
// thumb row: Miryoku's slot 1 keeps column 1 (the BACK key, so it stays on the
// key that is HYPER in BASE), then one column is skipped so its six thumb keys
// land on columns 4-9, centred over the pocket's thumb area and splitting the
// hands between the two Space keys. Columns 10-12 stay inert.
#define TM10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) a1, U_NP, a2, a3, a4, a5, a6, a7, a8, a9, a10, U_NP
// LAYOUT takes 64 arguments, and a macro argument that itself expands to a
// comma-separated list does not count as several arguments. Bouncing the
// already-expanded rows through a variadic macro re-parses them, so the rows
// land as individual keycode arguments.
#define POCKET_LAYOUT(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_MIRYOKU(r1, r2, r3, t) \
    POCKET_LAYOUT(RM10 r1, RM10 r2, RM10 r3, DEAD_ROW, TM10 t, MS_BTN3, MS_BTN1, MNT_SCRL, MS_BTN2)

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
    ),

    /* MIRYOKU -----------------------------------------------------------------
     *
     * Layout reminder (row 5 = Miryoku thumbs, row 4 inert):
     *   row1  alpha top      cols 1-5 | gap 6-7 | cols 8-12
     *   row2  home row mods  cols 1-5 | gap 6-7 | cols 8-12
     *   row3  alpha bottom   cols 1-5 | gap 6-7 | cols 8-12
     *   row4  inert
     *   row5  BACK at col 1, thumbs at cols 4-9, rest inert
     *
     * Thumbs, left to right: Esc/Media, Space/Nav, Tab/Mouse,
     *                        Enter/Sym, Backspace/Num, Delete/Fun.
     */
    [_M_BASE] = LAYOUT_MIRYOKU(
        (KC_Q              , KC_W              , KC_F              , KC_P              , KC_B              , KC_J              , KC_L              , KC_U              , KC_Y              , KC_QUOT           ),
        (LGUI_T(KC_A)      , LALT_T(KC_R)      , LCTL_T(KC_S)      , LSFT_T(KC_T)      , KC_G              , KC_M              , LSFT_T(KC_N)      , LCTL_T(KC_E)      , LALT_T(KC_I)      , LGUI_T(KC_O)      ),
        (LT(U_BUTTON,KC_Z) , ALGR_T(KC_X)      , KC_C              , KC_D              , KC_V              , KC_K              , KC_H              , KC_COMM           , ALGR_T(KC_DOT)    , LT(U_BUTTON,KC_SLSH)),
        (PDF(_BASE)        , U_NP              , LT(U_MEDIA,KC_ESC), LT(U_NAV,KC_SPC)  , LT(U_MOUSE,KC_TAB), LT(U_SYM,KC_ENT)  , LT(U_NUM,KC_BSPC) , LT(U_FUN,KC_DEL)  , U_NP              , U_NP              )
    ),
    [_M_BUTTON] = LAYOUT_MIRYOKU(
        (U_UND             , U_CUT             , U_CPY             , U_PST             , U_RDO             , U_RDO             , U_PST             , U_CPY             , U_CUT             , U_UND             ),
        (KC_LGUI           , KC_LALT           , KC_LCTL           , KC_LSFT           , U_NU              , U_NU              , KC_LSFT           , KC_LCTL           , KC_LALT           , KC_LGUI           ),
        (U_UND             , U_CUT             , U_CPY             , U_PST             , U_RDO             , U_RDO             , U_PST             , U_CPY             , U_CUT             , U_UND             ),
        (U_NP              , U_NP              , KC_BTN3           , KC_BTN1           , KC_BTN2           , KC_BTN2           , KC_BTN1           , KC_BTN3           , U_NP              , U_NP              )
    ),
    [_M_NAV] = LAYOUT_MIRYOKU(
        (U_NA              , U_NA              , U_NA              , U_NA              , U_NA              , U_RDO             , U_PST             , U_CPY             , U_CUT             , U_UND             ),
        (KC_LGUI           , KC_LALT           , KC_LCTL           , KC_LSFT           , U_NA              , KC_LEFT           , KC_DOWN           , KC_UP             , KC_RGHT           , CW_TOGG           ),
        (U_NA              , KC_ALGR           , U_NA              , U_NA              , U_NA              , KC_HOME           , KC_PGDN           , KC_PGUP           , KC_END            , KC_INS            ),
        (U_NP              , U_NP              , U_NA              , U_NA              , U_NA              , KC_ENT            , KC_BSPC           , KC_DEL            , U_NP              , U_NP              )
    ),
    [_M_MOUSE] = LAYOUT_MIRYOKU(
        (U_NA              , U_NA              , U_NA              , U_NA              , U_NA              , U_RDO             , U_PST             , U_CPY             , U_CUT             , U_UND             ),
        (KC_LGUI           , KC_LALT           , KC_LCTL           , KC_LSFT           , U_NA              , KC_MS_L           , KC_MS_D           , KC_MS_U           , KC_MS_R           , U_NU              ),
        (U_NA              , KC_ALGR           , U_NA              , U_NA              , U_NA              , KC_WH_L           , KC_WH_D           , KC_WH_U           , KC_WH_R           , U_NU              ),
        (U_NP              , U_NP              , U_NA              , U_NA              , U_NA              , KC_BTN2           , KC_BTN1           , KC_BTN3           , U_NP              , U_NP              )
    ),
    [_M_MEDIA] = LAYOUT_MIRYOKU(
        (U_NA              , U_NA              , U_NA              , U_NA              , U_NA              , UG_NEXT           , UG_HUEU           , UG_SATU           , UG_VALU           , UG_TOGG           ),
        (KC_LGUI           , KC_LALT           , KC_LCTL           , KC_LSFT           , U_NA              , KC_MPRV           , KC_VOLD           , KC_VOLU           , KC_MNXT           , U_NU              ),
        (U_NA              , KC_ALGR           , U_NA              , U_NA              , U_NA              , U_NU              , U_NU              , U_NU              , U_NU              , U_NA              ),
        (U_NP              , U_NP              , U_NA              , U_NA              , U_NA              , KC_MSTP           , KC_MPLY           , KC_MUTE           , U_NP              , U_NP              )
    ),
    [_M_NUM] = LAYOUT_MIRYOKU(
        (KC_LBRC           , KC_7              , KC_8              , KC_9              , KC_RBRC           , U_NA              , U_NA              , U_NA              , U_NA              , MNT_MENU          ),
        (KC_SCLN           , KC_4              , KC_5              , KC_6              , KC_EQL            , U_NA              , KC_LSFT           , KC_LCTL           , KC_LALT           , KC_LGUI           ),
        (KC_GRV            , KC_1              , KC_2              , KC_3              , KC_BSLS           , U_NA              , U_NA              , U_NA              , KC_ALGR           , U_NA              ),
        (U_NP              , U_NP              , KC_DOT            , KC_0              , KC_MINS           , U_NA              , U_NA              , U_NA              , U_NP              , U_NP              )
    ),
    [_M_SYM] = LAYOUT_MIRYOKU(
        (KC_LCBR           , KC_AMPR           , KC_ASTR           , KC_LPRN           , KC_RCBR           , U_NA              , U_NA              , U_NA              , U_NA              , U_NA              ),
        (KC_COLN           , KC_DLR            , KC_PERC           , KC_CIRC           , KC_PLUS           , U_NA              , KC_LSFT           , KC_LCTL           , KC_LALT           , KC_LGUI           ),
        (KC_TILD           , KC_EXLM           , KC_AT             , KC_HASH           , KC_PIPE           , U_NA              , U_NA              , U_NA              , KC_ALGR           , U_NA              ),
        (U_NP              , U_NP              , KC_LPRN           , KC_RPRN           , KC_UNDS           , U_NA              , U_NA              , U_NA              , U_NP              , U_NP              )
    ),
    /* Fun layer, keeping the pocket's own escapes on the right hand:
     * bootloader, EEPROM reset, and the OLED menu (Hyper+Enter in BASE).
     * The menu also sits on the top-right key of the Num layer (Backspace
     * thumb), which is easier to find than Del + top-right. */
    [_M_FUN] = LAYOUT_MIRYOKU(
        (KC_F12            , KC_F7             , KC_F8             , KC_F9             , KC_PSCR           , U_NA              , U_NA              , QK_BOOT           , QK_CLEAR_EEPROM   , MNT_MENU          ),
        (KC_F11            , KC_F4             , KC_F5             , KC_F6             , KC_SCRL           , U_NA              , KC_LSFT           , KC_LCTL           , KC_LALT           , KC_LGUI           ),
        (KC_F10            , KC_F1             , KC_F2             , KC_F3             , KC_PAUS           , U_NA              , U_NA              , U_NA              , KC_ALGR           , U_NA              ),
        (U_NP              , U_NP              , KC_APP            , KC_SPC            , KC_TAB            , U_NA              , U_NA              , U_NA              , U_NP              , U_NP              )
    ),
};

/* ------------------------------------------------------------------ toggle --
 *
 * HYPER + Shift + M switches to the Miryoku default layer, and the BACK key on
 * Miryoku's bottom row (PDF(_BASE)) comes back. Both are *persistent*
 * (PDF, not DF), so the choice survives reboots; QK_CLEAR_EEPROM on _M_FUN
 * resets it.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_M && layer_state_is(_HYPER) && (get_mods() & MOD_MASK_SHIFT)) {
        set_single_persistent_default_layer(_M_BASE);
        layer_clear();
        return false;
    }
    return true;
}
