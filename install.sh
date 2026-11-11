#!/usr/bin/env sh
printf "##########################\n"
printf "######### ploopy #########\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/ploopyco/trackball/keymaps/dbeley
cp -r ploopy/* ~/qmk_firmware/keyboards/ploopyco/trackball/keymaps/dbeley
# qmk compile -kb ploopyco/trackball/rev1 -km dbeley
printf "##########################\n"
printf "######### preonic ########\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/preonic/keymaps/dbeley
cp -r preonic/* ~/qmk_firmware/keyboards/preonic/keymaps/dbeley
# qmk compile -kb preonic/rev3 -km dbeley
printf "##########################\n"
printf "######### sofle ##########\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/sofle/keymaps/dbeley
cp -r sofle/* ~/qmk_firmware/keyboards/sofle/keymaps/dbeley
# qmk compile -kb sofle -km dbeley
printf "##########################\n"
printf "######### sofle-gamepad ##\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/sofle/keymaps/dbeley-gamepad
cp -r sofle-gamepad/* ~/qmk_firmware/keyboards/sofle/keymaps/dbeley-gamepad
# qmk compile -kb sofle -km dbeley-gamepad
printf "##########################\n"
printf "######### xd75 ###########\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/xd75/keymaps/dbeley
cp -r xd75/* ~/qmk_firmware/keyboards/xd75/keymaps/dbeley
# qmk compile -kb xd75 -km dbeley
printf "##########################\n"
printf "######### ymd21 ##########\n"
printf "##########################\n"
mkdir -p ~/qmk_firmware/keyboards/ymdk/np21/keymaps/dbeley
cp -r ymdk_np21/* ~/qmk_firmware/keyboards/ymdk/np21/keymaps/dbeley
# qmk compile -kb ymdk/np21 -km dbeley
printf "##########################\n"
printf "######### cantor miryoku #\n"
printf "##########################\n"
cp -r cantor-remix/* ~/qmk_firmware/users/manna-harbour_miryoku
# qmk compile -kb cantor -km manna-harbour_miryoku
printf "##########################\n"
printf "###### pocket reform ######\n"
printf "##########################\n"
# The RP2040 keyboard of the MNT Pocket Reform is driven by a QMK port that
# lives outside qmk_firmware, so it is cloned at a pinned commit and dropped in
# place of the stock MNT keyboards (which move to .disabled-mntre, a dot dir so
# QMK does not scan them).
pocket_port="https://codeberg.org/sleeplessval/qmk-pocket-reform"
pocket_pin="75057bb26ff4cdb6744a5c7e0db87a2fc8f8228c"
pocket_tmp="$(mktemp -d)"
git clone --quiet "$pocket_port" "$pocket_tmp/port"
git -C "$pocket_tmp/port" checkout --quiet "$pocket_pin"
mkdir -p ~/qmk_firmware/.disabled-mntre
mv ~/qmk_firmware/keyboards/mntre/* ~/qmk_firmware/.disabled-mntre/ 2>/dev/null
mv ~/qmk_firmware/keyboards/mntre_v3 ~/qmk_firmware/.disabled-mntre/ 2>/dev/null
mkdir -p ~/qmk_firmware/keyboards/mntre/pocket_reform_hid/keymaps/dbeley
cp -r "$pocket_tmp/port/." ~/qmk_firmware/keyboards/mntre/pocket_reform_hid/
cp pocket-reform/*.c pocket-reform/*.h pocket-reform/rules.mk \
  ~/qmk_firmware/keyboards/mntre/pocket_reform_hid/keymaps/dbeley/
rm -rf "$pocket_tmp"
# qmk compile -kb mntre/pocket_reform_hid -km dbeley
