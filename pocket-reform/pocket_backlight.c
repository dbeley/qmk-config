// SPDX-License-Identifier: GPL-2.0-or-later
//
// Host-controlled backlight colour, so the NixOS side (stylix theme) can keep
// driving the keyboard RGB the way it did with MNT's stock firmware.
//
// MNT's firmware accepted `xLRGB`/`xLBRT` output reports; QMK exposes a vendor
// raw HID endpoint instead, so the protocol here is a single 32-byte output
// report (no report id):
//
//   byte 0 : 'C' (0x43)
//   byte 1 : red    0-255
//   byte 2 : green  0-255
//   byte 3 : blue   0-255
//   byte 4 : value  0-255 (0 turns the backlight off)
//   bytes 5-31: unused
//
// Anything else is ignored so the report can grow later.

#include QMK_KEYBOARD_H

#define POCKET_BL_CMD_COLOUR 'C'

static uint8_t rgb_to_hue8(uint8_t r, uint8_t g, uint8_t b, uint8_t *sat, uint8_t *val) {
    int max = MAX(r, MAX(g, b));
    int min = MIN(r, MIN(g, b));
    int delta = max - min;
    int hue;

    *val = max;
    *sat = max ? (255 * delta) / max : 0;

    if (!delta) {
        hue = 0;
    } else if (max == r) {
        hue = 43 * (g - b) / delta;
    } else if (max == g) {
        hue = 85 + 43 * (b - r) / delta;
    } else {
        hue = 171 + 43 * (r - g) / delta;
    }

    if (hue < 0) {
        hue += 255;
    }
    return (uint8_t)hue;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < 5 || data[0] != POCKET_BL_CMD_COLOUR) {
        return;
    }

    uint8_t sat, val;
    uint8_t hue = rgb_to_hue8(data[1], data[2], data[3], &sat, &val);
    uint8_t brightness = data[4];

    if (brightness == 0) {
        rgblight_disable_noeeprom();
        return;
    }

    rgblight_enable_noeeprom();
    // _noeeprom: this runs on every USB enumeration, no need to wear the flash.
    rgblight_sethsv_noeeprom(hue, sat, brightness);
}
