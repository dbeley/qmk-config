#!/usr/bin/env sh
# Installs the keymaps in this repository into a qmk_firmware tree.
#
#   QMK_HOME      qmk_firmware checkout (default: ~/qmk_firmware)
#   MIRYOKU_HOME  miryoku_qmk checkout for the cantor keymap (default:
#                 ~/src/miryoku_qmk); skipped when it does not exist
QMK_HOME=${QMK_HOME:-$HOME/qmk_firmware}
MIRYOKU_HOME=${MIRYOKU_HOME:-$HOME/src/miryoku_qmk}

printf "##########################\n"
printf "######### ploopy #########\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/ploopyco/trackball/keymaps/dbeley"
cp -r ploopy/* "$QMK_HOME/keyboards/ploopyco/trackball/keymaps/dbeley"
# qmk compile -kb ploopyco/trackball/rev1_005 -km dbeley
printf "##########################\n"
printf "######### preonic ########\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/preonic/keymaps/dbeley"
cp -r preonic/* "$QMK_HOME/keyboards/preonic/keymaps/dbeley"
# qmk compile -kb preonic/rev3 -km dbeley
printf "##########################\n"
printf "######### sofle ##########\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/sofle/keymaps/dbeley"
cp -r sofle/* "$QMK_HOME/keyboards/sofle/keymaps/dbeley"
# qmk compile -kb sofle -km dbeley
printf "##########################\n"
printf "######### sofle-gamepad ##\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/sofle/keymaps/dbeley-gamepad"
cp -r sofle-gamepad/* "$QMK_HOME/keyboards/sofle/keymaps/dbeley-gamepad"
# qmk compile -kb sofle -km dbeley-gamepad
printf "##########################\n"
printf "######### xd75 ###########\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/xiudi/xd75/keymaps/dbeley"
cp -r xd75/* "$QMK_HOME/keyboards/xiudi/xd75/keymaps/dbeley"
# qmk compile -kb xiudi/xd75 -km dbeley
printf "##########################\n"
printf "######### ymd21 ##########\n"
printf "##########################\n"
mkdir -p "$QMK_HOME/keyboards/ymdk/np21/keymaps/dbeley"
cp -r ymdk_np21/* "$QMK_HOME/keyboards/ymdk/np21/keymaps/dbeley"
# qmk compile -kb ymdk/np21 -km dbeley
printf "##########################\n"
printf "######### cantor miryoku #\n"
printf "##########################\n"
# Upstream qmk_firmware dropped users/manna-harbour_miryoku, so the cantor
# keymap lives in a miryoku_qmk checkout (branch miryoku) instead.
if [ -d "$MIRYOKU_HOME/users/manna-harbour_miryoku" ]; then
  cp -r cantor-remix/* "$MIRYOKU_HOME/users/manna-harbour_miryoku"
  # cd "$MIRYOKU_HOME" && qmk compile -kb cantor -km manna-harbour_miryoku -e MIRYOKU_NAV=VI
else
  printf "skipping: no miryoku_qmk at %s\n" "$MIRYOKU_HOME"
fi
printf "##########################\n"
printf "###### pocket reform ######\n"
printf "##########################\n"
# The RP2040 keyboard of the MNT Pocket Reform is driven by a QMK port that
# lives outside qmk_firmware, so it is cloned at a pinned commit and dropped in
# place of the stock MNT keyboards (which move to .disabled-mntre, a dot dir so
# QMK does not scan them).
pocket_port="https://codeberg.org/sleeplessval/qmk-pocket-reform"
pocket_pin="b4ca2840fe55b02c7678b2475e096d7d52cbf7f9"
pocket_tmp="$(mktemp -d)"
git clone --quiet "$pocket_port" "$pocket_tmp/port"
git -C "$pocket_tmp/port" fetch --quiet origin "$pocket_pin"
git -C "$pocket_tmp/port" checkout --quiet "$pocket_pin"
mkdir -p "$QMK_HOME/.disabled-mntre"
if [ -f "$QMK_HOME/keyboards/mntre/mntre.c" ]; then
  mv "$QMK_HOME"/keyboards/mntre/* "$QMK_HOME/.disabled-mntre/" 2>/dev/null
  mv "$QMK_HOME/keyboards/mntre_v3" "$QMK_HOME/.disabled-mntre/" 2>/dev/null
fi
mkdir -p "$QMK_HOME/keyboards/mntre/pocket_reform_hid/keymaps/dbeley"
cp -r "$pocket_tmp/port/." "$QMK_HOME/keyboards/mntre/pocket_reform_hid/"
rm -rf "$QMK_HOME/keyboards/mntre/pocket_reform_hid/.git"
cp pocket-reform/*.c pocket-reform/*.h pocket-reform/rules.mk \
  "$QMK_HOME/keyboards/mntre/pocket_reform_hid/keymaps/dbeley/"
rm -rf "$pocket_tmp"
# qmk compile -kb mntre/pocket_reform_hid -km dbeley
