#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

enum preonic_layers {
  _QWERTY,
  _BEPO,
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  BEPO,
  DEFAULT,
  LOWER,
  RAISE,
  MUSIC1,
  MUSIC2,
  MUSIC3,
  MUSIC4,
  MUSIC5,
  MUSIC6,
  MUSIC7,
  MUSIC8,
  MUSIC9,
  MUSIC10,
  MUSIC11,
  MUSIC12,
};


#ifdef AUDIO_ENABLE
    float song_ode_to_joy[][2]  = SONG(ODE_TO_JOY);
    float song_rock_a_bye_baby[][2]  = SONG(ROCK_A_BYE_BABY);
    float song_doe_a_deer[][2]  = SONG(DOE_A_DEER);
    float song_imperial_march[][2] = SONG(IMPERIAL_MARCH); 
    float song_basketcase[][2] = SONG(BASKET_CASE);
    float song_mario_theme[][2] = SONG(MARIO_THEME);
    float song_mario_gameover[][2] = SONG(MARIO_GAMEOVER);
    float song_mario_mushroom[][2] = SONG(MARIO_MUSHROOM);
    float song_disney_song[][2] = SONG(DISNEY_SONG);
    float song_number_one[][2] = SONG(NUMBER_ONE);
    float song_all_star[][2] = SONG(ALL_STAR);
    float song_rick_roll[][2] = SONG(RICK_ROLL);
#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Meta | Alt  | Lower|           Space           | Raise| Alt  | Meta | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
        LGUI_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOT, 
        LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, 
        LSFT_T(KC_ESC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ESC), 
        KC_LCTL, KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_SPC, KC_SPC, KC_SPC, MO(4), KC_RALT, KC_RGUI, KC_RCTL),
/* Bépo
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   "  |   {  |   }  |   (  |   )  |   +  |   -  |   /  |   *  |   =  |  %   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   B  |   É  |   P  |   O  |   È  |   V  |   D  |   L  |   J  |   Z  |  W   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   U  |   I  |   E  |   ,  |   C  |   T  |   S  |   R  |   N  |  M   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   À  |   Y  |   X  |   .  |   K  |   '  |   Q  |   G  |   H  |   F  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Meta | Alt  | Lower|   Ç  |    Space    | BSpce| Raise| Alt  | Meta | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_BEPO] = LAYOUT_preonic_grid(
        BP_DOLLAR, BP_DQOT, BP_LCBR, BP_RCBR, BP_LPRN, BP_RPRN, BP_PLUS, BP_MINUS, BP_SLASH, BP_ASTR, BP_EQL, BP_PERC, 
        LGUI_T(KC_TAB), BP_B, BP_E_ACUTE, BP_P, BP_O, BP_E_GRAVE, BP_V, BP_D, BP_L, BP_J, BP_Z, BP_W, 
        LCTL_T(KC_ESC), BP_A, BP_U, BP_I, BP_E, BP_COMMA, BP_C, BP_T, BP_S, BP_R, BP_N, BP_M, 
        LSFT_T(KC_ESC), BP_AGRV, BP_Y, BP_X, BP_DOT, BP_K, BP_APOS, BP_Q, BP_G, BP_H, BP_F, RSFT_T(KC_ENT), 
        KC_LCTL, KC_LGUI, KC_LALT, MO(3), BP_CCED, KC_SPC, KC_SPC, KC_BSPC, MO(4), KC_RALT, KC_RGUI, KC_RCTL),
/* Default Qwerty Layout (the bootom row has been changed)
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Meta | Alt  | Lower|           Space           | Raise| Alt  | Meta | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_DEFAULT] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL, KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_SPC, KC_SPC, KC_SPC, MO(4), KC_RALT, KC_RGUI, KC_RCTL),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Print|  7   |  8   |  9   |  +   |  /   |  -   |  =   |  [   |  ]   |  \   | PgUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ScLck|  4   |  5   |  6   |  -   |  *   |  Ms1 | MsU  | Ms2  | Home | Del  | PgDwn|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Pause|  1   |  2   |  3   |  =   |      |  MsL | MsD  | MsR  | End  |  Up  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lock |  0   |  .   | MOD  | Pl/Pa| Vol- | Vol+ | Mute | MOD  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_PSCR, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PSLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, 
        KC_SLCK, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_PAST, KC_BTN1, KC_MS_U, KC_BTN2, KC_HOME, KC_DEL, KC_PGDN, 
        KC_PAUS, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_END, KC_UP, KC_TRNS, 
        KC_SLEP, KC_P0, KC_PDOT, KC_TRNS, KC_MPLY, KC_VOLD, KC_VOLU, KC_AUDIO_MUTE, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
/* Raise (Same as Lower)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Print|  7   |  8   |  9   |  +   |  /   |  -   |  =   |  [   |  ]   |  \   | PgUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ScLck|  4   |  5   |  6   |  -   |  *   |  Ms1 | MsU  | Ms2  | Home | Del  | PgDwn|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Pause|  1   |  2   |  3   |  =   |      |  MsL | MsD  | MsR  | End  |  Up  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Lock |  0   |  .   | MOD  | Pl/Pa| Vol- | Vol+ | Mute | MOD  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_PSCR, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PSLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, 
        KC_SLCK, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_PAST, KC_BTN1, KC_MS_U, KC_BTN2, KC_HOME, KC_DEL, KC_PGDN, 
        KC_PAUS, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_END, KC_UP, KC_TRNS, 
        KC_SLEP, KC_P0, KC_PDOT, KC_TRNS, KC_MPLY, KC_VOLD, KC_VOLU, KC_AUDIO_MUTE, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
/* Adjust (Lower + Raise)
* ,-----------------------------------------------------------------------------------.
* |  M1  |  M2  |  M3  |  M4  |  M5  |  M6  |  M7  |  M8  |  M9  |  M10 |  M11 |  M12 |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      | Reset| Debug|      |      |      |      |TermOn|TerOff|      |      |  Del |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |MusMod|Aud on|AudOff|      |      |Qwerty| Bépo |Defaul|      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |CkTogg|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      | MOD  | Back | Brig-  Brig+| Next | MOD  |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_ADJUST] = LAYOUT_preonic_grid(
        MUSIC1, MUSIC2, MUSIC3, MUSIC4, MUSIC5, MUSIC6, MUSIC7, MUSIC8, MUSIC9, MUSIC10, MUSIC11, MUSIC12, 
        KC_TRNS, RESET, DEBUG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TERM_ON, TERM_OFF, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, MU_MOD, AU_ON, AU_OFF, KC_TRNS, KC_TRNS, DF(_QWERTY), DF(_BEPO), DF(_DEFAULT), KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, CK_TOGG, MU_ON, MU_OFF, MI_ON, MI_OFF, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK, KC_BRID, KC_BRIU, KC_WFWD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MUSIC1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_ode_to_joy);
        #endif
      }
      return false;
      break;
    case MUSIC2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_rock_a_bye_baby);
        #endif
      }
      return false;
      break;
    case MUSIC3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_doe_a_deer);
        #endif
      }
      return false;
      break;
    case MUSIC4:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_imperial_march);
        #endif
      }
      return false;
      break;
    case MUSIC5:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_basketcase);
        #endif
      }
      return false;
      break;
    case MUSIC6:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_mario_theme);
        #endif
      }
      return false;
      break;
    case MUSIC7:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_mario_gameover);
        #endif
      }
      return false;
      break;
    case MUSIC8:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_mario_mushroom);
        #endif
      }
      return false;
      break;
    case MUSIC9:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_disney_song);
        #endif
      }
      return false;
      break;
    case MUSIC10:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_number_one);
        #endif
      }
      return false;
      break;
    case MUSIC11:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_all_star);
        #endif
      }
      return false;
      break;
    case MUSIC12:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(song_rick_roll);
        #endif
      }
      return false;
      break;
  }
  return true;
};

