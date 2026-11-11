// SPDX-License-Identifier: GPL-2.0-or-later
//
// Layout indicator for the OLED: names the active layout, and shows a short
// splash whenever it changes.
//
// The port's own screen code (menu, battery, confirm, hello, help) owns the
// display; this only draws while that code is idle (menu_screen == OFF).
// Burn-in is handled by QMK: the driver blanks the panel after OLED_TIMEOUT and
// turns it back on when there is input activity, so nothing here manages it.

#include QMK_KEYBOARD_H
#include <string.h>
#include "pocket_reform.h"

// The port's screen state lives in the keyboard directory, which is not on the
// include path for keymap sources.
#include "../../oled.h"

#define SPLASH_MS 2000
#define COLS 21

static char     shown[16];
static bool     on_screen;
static uint32_t splash_until;

static void write_centred(uint8_t line, const char *text) {
    uint8_t len = strlen(text);
    uint8_t col = (len < COLS) ? (COLS - len) / 2 : 0;
    oled_set_cursor(col, line);
    oled_write(text, false);
}

void housekeeping_task_user(void) {
    if (menu_screen != OFF) {
        // The port is drawing: redo our splash once it has finished.
        on_screen = false;
        return;
    }

    const char *name    = pocket_layout_name();
    bool        changed = strcmp(shown, name) != 0;
    if (changed) {
        strncpy(shown, name, sizeof(shown) - 1);
        shown[sizeof(shown) - 1] = '\0';
        splash_until              = timer_read32() + SPLASH_MS;
    }

    bool splashing = !timer_expired32(timer_read32(), splash_until);
    if (!changed && splashing == on_screen) {
        return;
    }

    // Nothing is drawn outside the splash: a label lit for 5s after every
    // keypress is exactly how these panels burn in.
    oled_clear();
    if (splashing) {
        write_centred(1, name);
    }
    on_screen = splashing;
}
