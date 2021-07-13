# qmk config files

I have several keyboards using QMK:
- xd75: 15x5 ortho
- preonic/rev3: 12x5 ortho
- ymdk_np21: 24-keys macropad
- sofle: ergonomic split ortho
- ploopyco/trackball/rev1: not a keyboard, a qmk-compatible trackball (I have the left-handed version)

## Install

### Preonic

```
make preonic/rev3:default
make preonic/rev3:default:dfu-util
```

RESET button on the bottom of the keyboard.

### XD75

```
make xd75:default
make xd75:default:flash
```

`MOD+k` to put the keyboard in bootloader mode

### Sofle

```
make sofle:default
make sofle:default:avrdude
```

Reset button when asked.
Disconnect first half, connect the second one and repeat the process.

### YMDK Macropad

```
make ymdk_np21:default
make ymdk_np21:default:flash
```

Hold down the Top Left Key (USB on top) while plugging in the keyboard.

### Ploopy Classic Trackball

```
make ploopyco/trackball/rev1_005:default:flash
```

To jump to the bootloader, hold down "Button 4" (immediate right of the trackball)
