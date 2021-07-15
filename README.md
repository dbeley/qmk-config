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

Sofle keyboard uses QMK Firmware and support for the board is part of the main QMK repository. There’s also a basic support in QMK Configurator but there’s no default layout yet and encoders are not supported.

Suggested approach is to build the firmware yourself. You should be familiar with QMK and be able to make it work on your local environment. If not, please follow the instructions in the documentation.

- Make sure your QMK environment is setup.
- Make sure halves are not connected together with TRRS cable.
- Connect one half to USB, flash the firmware (always follow the actuall instructions in the QMK documentation! The command might look something like this: qmk flash -kb sofle/rev1 -km default). Use the reset button to reset the keyboard when you are asked to in console.
- Connect the second half and flash it in the same way as the previous one.
- Disconnect the USB cable. Connect both halves together with TRRS cable.
- Connect USB cable to the left side (This can be changed, look for setting handednesss in QMK documentation).
- Enjoy SofleKeyboard!


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
- https://artsey.io/
- https://github.com/artseyio/artsey-qmk
- https://github.com/ploopyco/classic-trackball/wiki/Appendix-C%3A-QMK-Firmware-Programming
