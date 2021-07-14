# qmk config files

I have several keyboards using QMK:
- xd75: 15x5 ortho
- preonic/rev3: 12x5 ortho
- ymdk_np21: 24-keys macropad
- sofle: ergonomic split ortho
- ploopyco/trackball/rev1: not a keyboard, a qmk-compatible trackball (I have the left-handed version)

## Config files

- ploopy : done (tested)
- preonic : abandonned (to test)
- sofle : luna added, todo layout (to test)
- xd75 : refactoring done (to test)
- ymdk_np21 : todo (to test)

## Install

### Ploopy Classic Trackball

```
cp -r ploopy/* ~/qmk_firmware/keyboards/ploopyco/trackball/keymaps/dbeley
qmk compile -kb ploopyco/trackball/rev1 -km dbeley
```

Left-handed ploopy is rev1 not rev1_005

Make sure to change the `rev1/rules.mk` configuration file to have the line `BOOTLOADER=atmel-dfu` instead of `BOOTLOADER=caterina`.

To jump to the bootloader, hold down "Button 4" (immediate right of the trackball) or "Button 5" (next to Button 4) while plugging the USB cable to a computer (try both, as it's not 100% clear which button it is when you have a left-handed version).

```
qmk flash -kb ploopyco/trackball/rev1 -km dbeley
```

### Preonic

```
cp -r preonic/* ~/qmk_firmware/keyboards/preonic/keymaps/dbeley
qmk compile -kb preonic/rev3 -km dbeley
```

RESET button on the bottom of the keyboard.

```
qmk flash -kb preonic/rev3 -km dbeley
```

### Sofle

```
cp -r sofle/* ~/qmk_firmware/keyboards/sofle/keymaps/dbeley
qmk compile -kb sofle -km dbeley
```

Reset button when asked.
Disconnect first half, connect the second one and repeat the process.

```
qmk flash -kb sofle -km dbeley
```

### XD75

```
cp -r xd75/* ~/qmk_firmware/keyboards/xd75/keymaps/dbeley
qmk compile -kb xd75 -km dbeley
```

`MOD+k` to put the keyboard in bootloader mode

```
qmk flash -kb xd75 -km dbeley
```

### YMDK Macropad

```
cp -r ymdk/* ~/qmk_firmware/keyboards/ymdk_np21/keymaps/dbeley
qmk compile -kb ymdk_np21 -km dbeley
```

Hold down the Top Left Key (USB on top) while plugging in the keyboard.

```
qmk flash -kb ymdk_np21 -km dbeley
```

## Credits

- https://github.com/qmk/qmk_firmware
- https://github.com/artseyio/artsey-qmk
- https://github.com/ploopyco/classic-trackball/wiki/Appendix-C%3A-QMK-Firmware-Programming
