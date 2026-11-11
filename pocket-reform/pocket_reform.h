// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

enum pocket_layers {
    _BASE,
    _HYPER,
    // Miryoku layers; everything from here up is a Miryoku default layer.
    _M_BASE,
    _M_BASE_GALLIUM,
    _M_BUTTON,
    _M_NAV,
    _M_MOUSE,
    _M_MEDIA,
    _M_NUM,
    _M_SYM,
    _M_FUN,
    POCKET_LAYER_COUNT
};
