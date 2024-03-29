#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif // TAPPING_TERM
#define TAPPING_TERM 175

#define OLED_TIMEOUT 15000
#define OLD_BRIGHTNESS 120

#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

#define MASTER_RIGHT
