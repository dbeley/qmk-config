#include QMK_KEYBOARD_H

enum sofle_layers {
    _QWERTY,
    _RAISE,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_RAISE,
};


	const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 	/* QWERTY
 	 * ,-----------------------------------------.                    ,-----------------------------------------.
 	 * |      |      |      |      |      |      |                    |  Esc |   1  |   2  |   3  |   4  |  5   |
 	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |                    |  Tab |   Q  |   W  |   E  |   R  |  T   |
 	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |-------.    ,-------|   U  |   A  |   S  |   D  |   F  |  G   |
 	 * |------+------+------+------+------+------| MUTE  |    | MUTE  |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |-------|    |-------|  Ctrl|   Z  |   X  |   C  |   V  |  B   |
 	 * `-----------------------------------------/       /     \      \-----------------------------------------'
 	 *            |      |      |      |      | /       /       \ RAISE\  | Shft | Spce | Ent  | M    |
 	 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 	 *            `-----------------------------------'           '------''---------------------------'
 	 */
	[_QWERTY] = LAYOUT( \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_ESC,   KC_1,  KC_2,   KC_3,   KC_4,   KC_5, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_TAB,   KC_Q,  KC_W,   KC_E,   KC_R,   KC_T, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_U,     KC_A,  KC_S,   KC_D,   KC_F,   KC_G, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_MUTE,     KC_MUTE, KC_LCTL,  KC_Z,  KC_X,   KC_C,   KC_V,   KC_B, \
      	    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_RAISE, KC_LSFT, KC_SPC, KC_ENT, KC_M \
	),
	/* RAISE
 	 * ,-----------------------------------------.                    ,-----------------------------------------.
 	 * |      |      |      |      |      |      |                    |  F10 |  F11 | F12  |  7   |  8   |  9   |
 	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |                    |  F7  |  F8  | F9   |  4   |  5   |  6   |
 	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |-------.    ,-------|  F4  |  F5  | F6   |  1   |  2   |  3   |
 	 * |------+------+------+------+------+------| MUTE  |    | MUTE  |------+------+------+------+------+------|
 	 * |      |      |      |      |      |      |-------|    |-------|  F1  |  F2  | F3   |  0   |  H   |  J   |
 	 * `-----------------------------------------/       /     \      \-----------------------------------------'
 	 *            |      |      |      |      | /       /       \      \  |  Tab | Play | Del  | Bspc |
 	 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 	 *            `-----------------------------------'           '------''---------------------------'
 	 */
	[_RAISE] = LAYOUT( \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_F10, KC_F11, KC_F12, KC_7,   KC_8,   KC_9, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_F7,  KC_F8,  KC_F9,  KC_4,   KC_5,   KC_6, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                           KC_F4,  KC_F5,  KC_F6,  KC_1,   KC_2,   KC_3, \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,       _______, KC_F1,  KC_F2,  KC_F3,  KC_0,   KC_H,   KC_J, \
         	 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                      _______, KC_TAB, KC_MPLY, KC_DEL, KC_BSPC \
	),

	};

/* Smart Backspace Delete */
bool            shift_held = false;
static uint16_t held_shift = 0;
/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            if (shift_held) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_VOLD);
            }
        } else {
            if (shift_held) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_VOLU);
            }
        }
    } else if (index == 1) {
        if (clockwise) {
            if (shift_held) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_VOLD);
            }
        } else {
            if (shift_held) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_VOLU);
            }
        }
    }
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case KC_RSFT:
        case KC_LSFT:
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    }
    return true;
}

#ifdef OLED_ENABLE

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
/* Sit */
static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },
/* 'sit2', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
/* Walk */
static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },
/* 'walk2', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }};
/* Run */
static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, },
/* 'run2', 32x22px */
{0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }};
/* Sneak */
static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, },
/* 'sneak2', 32x22px */
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);
        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);
        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);
        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

static void print_status_primary(void) {
    oled_set_cursor(0, 0);
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 0);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);
    oled_set_cursor(0, 1);
    oled_write(" wpm", false);

    oled_set_cursor(0, 3);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0, 5);
    oled_write("LAYER", false);
    oled_set_cursor(0, 6);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("Base ", false);
            break;
        case _RAISE:
            oled_write("Raise", false);
            break;
        default:
            oled_write("Undef", false);
    }
    render_luna(0,12);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

static const char PROGMEM text_clean[512] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f,
  0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xfe, 0xf9, 0xf1, 0xc3, 0x83, 0x03, 0x03,
  0x03, 0x83, 0xc3, 0xf1, 0xf9, 0xfc, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0x7e, 0x7c,
  0x3e, 0x1f, 0x7f, 0x7f, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f,
  0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0,
  0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe1, 0x01, 0x03, 0x03, 0x07, 0x07,
  0x87, 0xc3, 0xf3, 0xf9, 0xf9, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe,
  0x3f, 0x1f, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x8f, 0xc3, 0xc1, 0xc0,
  0x00, 0x9e, 0xde, 0xde, 0xdf, 0xdf, 0xcf, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0x1f, 0x0f, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0xc7, 0xe7, 0xf7, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7f, 0x7e, 0xf8, 0xf0, 0xf0, 0xf0,
  0xf0, 0xf0, 0xf8, 0x7e, 0x7f, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x3c, 0x3c, 0x01, 0x01,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x80,
  0xc0, 0xf0, 0xf8, 0xfe, 0x7f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xcf, 0xef, 0xef, 0xef,
  0x87, 0xc3, 0xef, 0xef, 0xef, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x0f, 0x07, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7c, 0x78, 0xf8, 0xf8,
  0xf8, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char PROGMEM text_glitch[5][512] = {
  {
    // frame 1
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1c, 0x1e, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xfe, 0xf9, 0xf1, 0xc3, 0x83, 0x03, 0x03,
    0x03, 0x83, 0xc3, 0xf1, 0xf9, 0xfe, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0x7e, 0x7c,
    0x7e, 0x3f, 0x1f, 0x7f, 0x7b, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0x3e, 0x3f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1c, 0x1e, 0x9f, 0xdf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0f, 0x3b, 0xf3, 0xf3, 0xf0, 0xe0, 0xc0,
    0xc0, 0xc0, 0xc8, 0xcc, 0xec, 0xfc, 0xf7, 0xf3, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x80, 0xc1, 0xc3, 0x07, 0x07,
    0x07, 0x03, 0x33, 0xbb, 0xfb, 0xfb, 0xf9, 0xf8, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0xbe, 0xbf, 0xc1, 0xe1, 0xf9, 0x7c, 0x7e,
    0x3e, 0x1e, 0x86, 0x87, 0xff, 0xff, 0x7f, 0x7f, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x8f, 0xc3, 0xc1, 0xc0, 0xc0, 0x1e,
    0x9e, 0xde, 0xdf, 0xdf, 0xcf, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0x3f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0xc7, 0xe7, 0xf7, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x0f, 0x3e, 0x7c, 0x7c, 0xf8, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf2, 0xfb, 0x7f, 0x7f, 0x3d, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x3c, 0x3c, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x80, 0xc0,
    0xf0, 0xf8, 0xf8, 0x7e, 0x3f, 0x0f, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xcf, 0xef, 0xef, 0xef, 0x87,
    0xc3, 0xef, 0xef, 0xef, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x7c, 0xfe, 0xff, 0xef, 0x07, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0xf3, 0xfb, 0xfb, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7c, 0x78, 0xf8, 0xf8,
    0xf8, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    // frame 2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x0f, 0x0f, 0x07, 0x07, 0x07,
    0x1f, 0x1f, 0x7c, 0x7c, 0x7c, 0x7c, 0xdf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xe7, 0xdf, 0x3f, 0x3f, 0xf8, 0xf0, 0xf0, 0xf0,
    0xc0, 0xc0, 0x80, 0xe0, 0xfc, 0xfe, 0x3f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x0f, 0x1e, 0x7e, 0xfe, 0xf0, 0xe0,
    0x81, 0x01, 0x0f, 0x0f, 0x0f, 0xc3, 0xe7, 0xff, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0x9f, 0xdf,
    0xdf, 0xdf, 0xf8, 0x7e, 0xff, 0xff, 0xef, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x1f, 0x0f, 0x0f,
    0x07, 0x07, 0x7c, 0x7c, 0x7d, 0x7d, 0x7d, 0x7c, 0xdf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x7f, 0xf8, 0xf0,
    0xf0, 0xf0, 0x00, 0x00, 0x80, 0xe0, 0xfc, 0xfe, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0x04, 0x04, 0x00, 0x00, 0x80,
    0x81, 0xc1, 0xdf, 0xef, 0xef, 0xef, 0xe7, 0xe3, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0xf8, 0xf8, 0xfe, 0x7f, 0x3f, 0x3f, 0x1f, 0x07,
    0x07, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe3, 0xe3, 0xf0, 0xf0, 0xf0, 0xc0, 0xde, 0xde,
    0xde, 0xdf, 0x7f, 0xcf, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x1f, 0xff, 0xff, 0xff, 0xc7, 0x03, 0x01, 0x01, 0x01,
    0x06, 0x07, 0x1f, 0x07, 0x1f, 0x1c, 0x98, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x87, 0x8f, 0x3f, 0x3e, 0x7c, 0x7c, 0xfc,
    0xf0, 0xf0, 0x20, 0xe0, 0xf8, 0x3f, 0x1f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x00, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xe0, 0xc0,
    0xf0, 0xf8, 0xf8, 0xfc, 0xff, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0xc1, 0xe1, 0xf1, 0xf3, 0xfb, 0xfb, 0xfb, 0xe7,
    0xe3, 0xef, 0xbf, 0x81, 0xbc, 0xc0, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x07, 0x0f, 0xff, 0xf9, 0xf8, 0xe0, 0x00, 0x01,
    0x03, 0x03, 0x0f, 0x0f, 0x0b, 0x0b, 0x98, 0xd0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x1f, 0x1e,
    0x3e, 0x3e, 0xe0, 0xe0, 0xf0, 0x00, 0xff, 0xff, 0x7f, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    // frame 3
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0xf8, 0xfc, 0xfe, 0xfe, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xa3, 0x5f, 0xff, 0xfc, 0xfc, 0xe0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xe0, 0xfb, 0xff, 0x3f, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x3f, 0x7c, 0xf8, 0xfb, 0xc3, 0x83, 0x03,
    0x03, 0x03, 0x83, 0xc1, 0xf1, 0xfe, 0xff, 0x7f, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x3c, 0x3c, 0x3c, 0x7d, 0x7f, 0x7f, 0x7f, 0x3e,
    0x1c, 0x7e, 0x7f, 0x7f, 0x0f, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xfc, 0x7e, 0x3e, 0x3f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1c, 0x1e, 0x9f, 0xdf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x7f, 0xff, 0xfc, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf0, 0xc1, 0x03, 0x03, 0x07, 0x07, 0x07,
    0x83, 0xf3, 0xfb, 0xf9, 0xf8, 0xf8, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x1f, 0x10, 0x10, 0x18, 0xec, 0xee,
    0xff, 0xff, 0xf7, 0x37, 0x1f, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0x8f,
    0xc3, 0xc1, 0xc0, 0xc0, 0xde, 0x1e, 0x4f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x1f, 0x0f,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xf7, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x3f, 0xff, 0xff, 0xf8,
    0xf0, 0xf0, 0xf0, 0xf0, 0x10, 0x18, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xfc, 0xfe, 0xfe, 0x3c, 0x3c, 0x01,
    0x01, 0x01, 0x00, 0x00, 0xe0, 0xf8, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0x07, 0x07, 0x07, 0x80,
    0xc0, 0xf0, 0xf8, 0xf8, 0x7f, 0x3f, 0x0f, 0x07, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x87, 0xc7, 0xcf, 0xef,
    0xef, 0xeb, 0xe7, 0xe7, 0x8f, 0xc8, 0xe8, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xfe, 0xff, 0xff, 0x87, 0x07, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x1f, 0x7f, 0x7f, 0xfc, 0xf8,
    0xf8, 0x78, 0x78, 0x38, 0x3c, 0x1f, 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    // frame 4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1c, 0x1e, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xfe, 0xf9, 0xf1, 0xc3, 0x83, 0x03,
    0x03, 0x03, 0x83, 0xc3, 0xf1, 0xf9, 0xfe, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0x7e,
    0x7c, 0x3e, 0x1f, 0x7f, 0x7f, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0x3e, 0x3f, 0x1f,
    0x1f, 0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x27, 0xff, 0xff, 0xf8, 0xf8, 0xc0, 0xc0,
    0xc0, 0xc0, 0xe0, 0xe0, 0xf8, 0xff, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe0, 0x01, 0x03, 0x03, 0x03, 0x07,
    0xc7, 0xf3, 0xfb, 0xfb, 0xf9, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe,
    0x1f, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x8b, 0xc1, 0xc0,
    0xc6, 0xde, 0x1e, 0x9f, 0xdf, 0xdf, 0xcf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0x3f, 0x0f, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0xc7, 0xe7, 0xf7, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7f, 0x7e, 0xf8, 0xf0, 0xf0,
    0xf0, 0xf0, 0xf8, 0x7e, 0x7f, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x3c, 0x3c, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x80, 0xf0, 0xf8, 0xfe, 0x7f, 0x3f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xcf, 0xef, 0xef,
    0xef, 0xe3, 0x8f, 0xcf, 0xef, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x0f, 0x07, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7c, 0x78, 0xf8,
    0xf8, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    // frame 5
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x7c, 0x7c, 0x1c,
    0x1e, 0x1f, 0x1f, 0x8f, 0xcf, 0xef, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xe1, 0x80, 0x00, 0x00, 0x00, 0xc0,
    0xc0, 0xe0, 0xf8, 0xff, 0x7f, 0x9f, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0xfb, 0xe7, 0xc7, 0x0f, 0x0f, 0x0f, 0x0f, 0x03,
    0x83, 0xc3, 0xf1, 0xfc, 0x7e, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe1, 0xe3, 0xef, 0xff, 0xff, 0xfe, 0xf8, 0xf0, 0x3e,
    0x1f, 0x7f, 0x7f, 0xbd, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0xc1, 0xe1, 0xf1, 0xf9, 0x7d, 0x7d, 0x7d, 0x1c,
    0x1e, 0x1f, 0x1f, 0x8f, 0xcf, 0xef, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xe1, 0x80, 0x00, 0x00, 0x00, 0xc0,
    0xc0, 0xe0, 0xf8, 0xff, 0x7f, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x87, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x87,
    0xc3, 0xf3, 0xf9, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xfe, 0x00, 0x80, 0xe0, 0xf0, 0xf9,
    0x3f, 0x1f, 0x07, 0x07, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x3f, 0x0f, 0x07, 0x03,
    0x00, 0x9e, 0xde, 0xde, 0xef, 0xef, 0xe7, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f,
    0x07, 0x07, 0x07, 0x07, 0xe3, 0xf3, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0,
    0xf0, 0xf0, 0xf8, 0x7e, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe0, 0xf1, 0xf1, 0xf3, 0xf3, 0x07, 0x07,
    0x01, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xc0, 0xf0, 0xf8, 0xfe, 0xbf, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3c, 0xbc, 0xbc, 0xbe,
    0x87, 0xc3, 0xef, 0xef, 0xf7, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xfc, 0x3e, 0x1f, 0x0f, 0x0f, 0x0f,
    0x03, 0x03, 0x03, 0x03, 0xf1, 0xf9, 0xfd, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x7f, 0xff, 0xfc, 0xf0, 0xe0, 0xe0, 0xe0,
    0xf8, 0x78, 0x7c, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

bool glitch = true;
uint8_t frame_count = 15;
uint16_t arasaka_timer;

void arasaka_text_clean(void)
{
  oled_write_raw_P(text_clean, 512);
}

void arasaka_text_glitch(void)
{
  uint8_t frame = rand() % 5;
  oled_write_raw_P(text_glitch[frame], 512);
}

void arasaka_draw(void) {
  uint16_t timer = timer_elapsed(arasaka_timer);

  if (timer < 150) {
    arasaka_text_glitch();
    return;
  }

  if (timer < 250) {
    arasaka_text_glitch();
    return;
  }

  if (timer > 9750 && timer < 9850) {
    arasaka_text_glitch();
    return;
  }

  if (timer > 9850 && timer < 10000) {
    arasaka_text_glitch();
    return;
  }

  if (timer > 10000) {
    arasaka_timer = timer_read();
  }

  if (glitch && 0 != frame_count) {
    frame_count--;
    arasaka_text_glitch();
    return;
  }

  glitch = false;

  arasaka_text_clean();

  if (1 == rand() % 50) {
    glitch = true;
    frame_count = 2 + rand() % 10;
  }
}

bool oled_task_user(void) {
    if (current_wpm == -1) {
    	set_current_wpm(0);
    }
    current_wpm   = get_current_wpm();

    if (is_keyboard_master()) {
        print_status_primary();
    }
    else {
        arasaka_draw();
    }
    return false;
}

#endif
