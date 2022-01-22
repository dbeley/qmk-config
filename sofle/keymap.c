#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LGUI |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTR |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------| MUTE  |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |Space | /LOWER  /       \RAISE \  |Space | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,  KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC, \
  LGUI_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_QUOT, \
  LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,                           KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT, \
  LSFT_T(KC_ESC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,          XXXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RSFT_T(KC_ESC), \
                 KC_LGUI, KC_LALT, KC_LCTRL, KC_SPC, KC_LOWER,    KC_RAISE, KC_SPC, KC_RCTRL, KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F4  |  F6  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | HOME | END  | RALT | PRT  | DEL  | BSPC |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | PGUP | RGUI | LALT | RSFT | RCTL | ENT  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | PGDN |  \   |  [   |  ]   |   =  |  -   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Prev | Next | Play | Mute | /LOWER  /       \RAISE \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT( \
KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                            _______, _______, _______, _______, _______, _______, \
KC_HOME,KC_END,RALT_T(KC_ESC),KC_PSCR,KC_DEL,KC_BSPC,                        _______, _______, _______, _______, _______, _______, \
KC_PGUP,LGUI_T(KC_TAB),LALT_T(KC_ESC),LSFT_T(KC_ESC),LCTL_T(KC_ESC),KC_ENT,  _______, _______, _______, _______, _______, _______, \
KC_PGDN, KC_BSLS, KC_LBRC, KC_RBRC, KC_EQL, KC_MINS,_______,        _______, _______, _______, _______, _______, _______, _______, \
             KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, _______,               _______, _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | BSPC | DEL  | PRT  | RALT | HOME | END  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| ENT  | RCTL | RSFT | LALT | RGUI | PGUP |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|  -   |   =  |   [  |   ]  |  \   | PGDN |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /LOWER  /       \RAISE \  | Mute | Play | Prev | Next |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
_______, _______, _______, _______, _______, _______,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,\
_______, _______, _______, _______, _______, _______,                      KC_BSPC, KC_DEL,KC_PSCR,RALT_T(KC_ESC),KC_HOME,KC_END,\
_______, _______, _______, _______, _______, _______,KC_ENT,RCTL_T(KC_ESC),RSFT_T(KC_ESC),LALT_T(KC_ESC), RGUI_T(KC_TAB),KC_PGUP,\
_______, _______, _______, _______, _______, _______, _______,        _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,KC_BSLS,KC_PGDN,\
             _______, _______, _______, _______, _______,               _______, KC_MUTE, KC_MPLY, KC_MPRV, KC_MNXT \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | VOLDO| MUTE | VOLUP|                    | PGUP | Del  | Up   | Bspc | Home |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VOLDO| MUTE | VOLUP| PREV | PLAY | NEXT |-------.    ,-------| PGDW | Left | Down | Right| End  |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | PREV | PLAY | NEXT |      | Bspc | ENT  |-------|    |-------| ENT  | Bspc |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |Space | /LOWER  /       \RAISE \  |Space | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_ADJUST] = LAYOUT( \
  _______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______, \
  _______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______, \
  _______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______, \
  _______,_______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,_______, \
               _______,_______,_______,_______,_______,         _______,_______,_______,_______,_______ \
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | `    |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LGUI | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCTR | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |Space | /LOWER  /       \RAISE \  |Space | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
};


int current_wpm = -1; // Enable screen-on at startup
bool isJumping = false;
bool showedJump = true;
static const char PROGMEM qmk[] = {
    0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf0, 0xf0, 0xf8, 0xf8, 0xf0, 0xf0, 0xf8,
    0xf8, 0xf0, 0xf0, 0xf8, 0xf8, 0xf0, 0xf0, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
    0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x99, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf1, 0xf3, 0xe3, 0xe7, 0x00,
    0x00, 0xe7, 0xe3, 0xf3, 0xf1, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0f, 0x0f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f,
    0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00,
};

#ifdef OLED_DRIVER_ENABLE

#ifdef MAIN_BOARD
static void render_logos(void){}
void luna_jump(bool newJump){
    isJumping = newJump;
    if (newJump) {
        showedJump = false;
    }
}

// START Luna vars
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint8_t current_frame = 0;

bool isSneaking = false;
static void render_luna(int LUNA_X, int LUNA_Y) {

    static const char PROGMEM sit[2][ANIM_SIZE] = {
        // 'sit1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sit2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    static const char PROGMEM walk[2][ANIM_SIZE] = {
        // 'walk1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
            0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
            0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'walk2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
            0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    static const char PROGMEM run[2][ANIM_SIZE] = {
        // 'run1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
            0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'run2', 32x22px
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
            0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        // 'sneak1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
            0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
            0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sneak2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
            0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
            0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // animation state
    void animation_phase(void) {

        if (isJumping || !showedJump) {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y +2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y -1);

            showedJump = true;
        } else {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y);
        }

        current_frame = (current_frame + 1) % 2;

        if(isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    // animation timer
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }

}
// END Luna vars


static void main_board(void) {
    int layer = get_highest_layer(layer_state);
    isSneaking = false;
    // Print current mode
    oled_write_ln_P(PSTR("Flare"), false);
    oled_write_ln_P(PSTR("Sofle"), false);
    if (layer == _FF14) {
        oled_write_raw_P(ffxiv, 16*8);
    } else if (keymap_config.swap_lalt_lgui) {
        oled_write_raw_P(windows, 16*8);
    } else {
        oled_write_raw_P(apple, 16*8);
    }
    oled_set_cursor(0, 9);

    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("ALL"), false);
            oled_write_P(PSTR(" YOUR"), false);
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _MOUS:
            isSneaking = true;
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case _SYMS:
            oled_write_ln_P(PSTR("@$*&#"), false);
            break;
        case _FF14:
            oled_write_ln_P(PSTR("FFXIV"), false);
            break;
        case _ESDF:
            oled_write_ln_P(PSTR("ESDF "), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    if (layer != _BASE) {
        oled_write_P(PSTR("\n"), false);
    }

    // Don't re-write if not in use
    if (current_wpm > 0) {
        render_luna(0,13);
    }
}

// End "MAIN_BOARD"
#else
static void main_board(void){}
static void luna_jump(bool newJump){}

#define MARQUEE_FRAME_DURATION 200 // how long each frame lasts in ms
#define LOGO_BYTES 128
#define LOGO_COUNT 7
static const char *const secondary_logos[] = { js, apple, docker, python, qmk, brew, windows };
#define MARQUEE_FRAMES (LOGO_COUNT * 4)
#define MARQUEE_SIZE ( LOGO_COUNT * LOGO_BYTES)
#define MARQUEE_SCROLL_UP true
uint32_t marquee_timer = 0;
uint32_t marquee_frame = 0;

static void render_logos(void) {
    void marquee_phase(void) {
        marquee_frame = (marquee_frame + 1) % MARQUEE_FRAMES;
        int marquee_start = MARQUEE_SIZE - (marquee_frame * 32);
        static char output[MARQUEE_SIZE];
        for (int i = 0; i < LOGO_COUNT; i++) {
            for (int j = 0; j < LOGO_BYTES; j++) {
                int pos = ( i * LOGO_BYTES + j + marquee_start ) % MARQUEE_SIZE;
                output[pos] = pgm_read_byte_near(secondary_logos[i] + j);
            }
        }
        oled_write_raw(output, MARQUEE_SIZE);
    }

    // animation timer
    if(timer_elapsed32(marquee_timer) > MARQUEE_FRAME_DURATION) {
        marquee_timer = timer_read32();
        marquee_phase();
    }
}

// End "MAIN_BOARD" false
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) {
    // Prevent blank screen on startup
    if (current_wpm == -1) {
        set_current_wpm(10);
    }
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        // can't gate main_board on wpm; won't get mode changes that don't trigger wpm
        main_board();
    } else if (current_wpm > 0) {
        render_logos();
    }
}

// End "OLED_DRIVER_ENABLE"
#else
static void luna_jump(bool newJump){}
// End "OLED_DRIVER_ENABLE" false
#endif

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            if (shift_held) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_VOLU);
            }
        } else {
            if (shift_held) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_VOLD);
            }
        }
    } else if (index == 1) {
        if (clockwise) {
            if (shift_held) {
                tap_code(KC_WH_R);
            } else {
                tap_code(KC_WH_D);
            }
        } else {
            if (shift_held) {
                tap_code(KC_WH_L);
            } else {
                tap_code(KC_WH_U);
            }
        }
    }
    return true;
}

#endif
