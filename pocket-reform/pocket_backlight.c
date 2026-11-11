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
//   byte 4 : value  0-255, 0xFF = keep the keyboard's current brightness,
//           0 = backlight off
//   bytes 5-31: unused
//
// Brightness is the keyboard's own: the trackball adjusts hue and brightness
// while HYPER is held (trackball.c) and stores them in EEPROM, so the host
// leaves byte 4 at 0xFF unless someone really wants to pin it.
//
// Anything else is ignored so the report can grow later.

#include QMK_KEYBOARD_H

#define POCKET_BL_CMD_COLOUR 'C'
#define POCKET_BL_KEEP_VAL 0xFF

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

    uint8_t r = data[1], g = data[2], b = data[3];
    uint8_t brightness = data[4];

    if (brightness == POCKET_BL_KEEP_VAL) {
        brightness = rgblight_get_val();
    }
    if (brightness == 0) {
        rgblight_disable_noeeprom();
        return;
    }

    uint8_t sat, val;
    uint8_t hue = rgb_to_hue8(r, g, b, &sat, &val);

    rgblight_enable_noeeprom();
    // _noeeprom: this runs on every USB enumeration, no need to wear the flash.
    // Keeping the HSV config in sync makes the trackball's hue/brightness
    // gesture start from what is actually on screen.
    rgblight_sethsv_noeeprom(hue, sat, brightness);
    // ...then write the exact colour the host asked for, scaled by brightness:
    // the HSV round trip goes through QMK's CIE curve, which would shift it.
    rgblight_setrgb((uint16_t)r * brightness / 255, (uint16_t)g * brightness / 255, (uint16_t)b * brightness / 255);
}
