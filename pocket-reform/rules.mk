# SPDX-License-Identifier: GPL-2.0-or-later

RAW_ENABLE = yes
CAPS_WORD_ENABLE = yes

# QMK only compiles keymap.c by itself; extra keymap sources must be listed.
SRC += pocket_backlight.c
SRC += oled_user.c
