# qmk config files

Some config files for the following QMK-compatible devices:
- xd75: 15x5 ortho
- preonic/rev3: 12x5 ortho
- ymdk/ymd21/v2: 24-keys macropad
- sofle: ergonomic split ortho
- ploopyco/trackball/rev1: trackball (I have the left-handed version)

## Install

You can either install the `qmk` utility or use qmk from source.

From source:
```
git clone https://github.com/qmk/qmk_firmware
make git-submodule
```

The YMDK macropad will need a custom fork of qmk in order to use my own keymap. Instructions are available in the [artseyio/artsey-qmk](https://github.com/artseyio/artsey-qmk) repository.

### Ploopy Classic Trackball

```
cp -r ploopy/* ~/qmk_firmware/keyboards/ploopyco/trackball/keymaps/dbeley
```

Flashing QMK on a left-handed ploopy is a bit different than flashing it on a right-handed one.

- left-handed ploopy is rev1 not rev1_005
- edit `rev1/rules.mk` to have the line `BOOTLOADER=atmel-dfu` instead of `BOOTLOADER=caterina`

To jump to the bootloader, hold down "Button 4" (immediate right of the trackball, immediate left if you have a left-handed model) while plugging the USB cable to a computer.

```
qmk flash -kb ploopyco/trackball/rev1 -km dbeley
# or
make ploopyco/trackball/rev1:dbeley:flash
```

### Preonic

```
cp -r preonic/* ~/qmk_firmware/keyboards/preonic/keymaps/dbeley
```

RESET button on the bottom of the keyboard.

```
qmk flash -kb preonic/rev3 -km dbeley
# or
make preonic/rev3:dbeley:dfu-util
```

### Sofle

```
cp -r sofle/* ~/qmk_firmware/keyboards/sofle/keymaps/dbeley
```

Press Reset button when asked.
Disconnect first half, connect the second one and repeat the process.

- Make sure your QMK environment is setup.
- Make sure halves are not connected together with TRRS cable.
- Connect one half to USB, flash the firmware. Press the reset button when asked.
- Connect the second half and flash it in the same way as the previous one.
- Disconnect the USB cable. Connect both halves together with TRRS cable.
- Connect USB cable to the left side (This can be changed, look for setting handednesss in QMK documentation).

```
qmk flash -kb sofle -km dbeley; qmk flash -kb sofle -km dbeley
# or
make sofle:dbeley:avrdude
```

### XD75

```
cp -r xd75/* ~/qmk_firmware/keyboards/xd75/keymaps/dbeley
```

`MOD+k` to put the keyboard in bootloader mode

```
qmk flash -kb xd75 -km dbeley
# or
make xd75:dbeley:flash
```

### YMDK Macropad

```
cp -r ymdk_np21/* ~/qmk_firmware/keyboards/ymdk/np21/keymaps/dbeley
```

Hold down the Top Left Key (USB on top) while plugging in the keyboard.

```
qmk flash -kb ymdk/np21 -km dbeley
# or
make ymdk/np21:dbeley:flash
```

### Cantor Remix

Hold top-left key and plug USB (top-right for right part).

If it doesn't work, you can also press the BOOT button below the micro-controller before plugging the board to the computer (both halves need to be disconnected from each other).

```
qmk flash -kb cantor -km manna-harbour_miryoku -e MIRYOKU_NAV=VI; qmk flash -kb cantor -km manna-harbour_miryoku -e MIRYOKU_NAV=VI
```

## Credits

- https://github.com/qmk/qmk_firmware
- https://artsey.io/
- https://github.com/artseyio/artsey-qmk
- https://github.com/ploopyco/classic-trackball/wiki/Appendix-C%3A-QMK-Firmware-Programming
