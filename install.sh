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
