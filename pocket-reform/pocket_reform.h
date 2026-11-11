// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

enum pocket_layers {
    _BASE,
    _HYPER,
    POCKET_LAYER_COUNT
};

bool pocket_is_miryoku(void);
const char *pocket_layout_name(void);
