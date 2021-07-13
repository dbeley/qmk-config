#!/usr/bin/env sh
printf "##########################\n"
printf "######### ploopy #########\n"
printf "##########################\n"
cp -r ploopy/* ~/qmk_firmware/keyboards/ploopyco/trackball/keymaps/dbeley
qmk compile -kb ploopyco/trackball/rev1_005 -km dbeley
printf "##########################\n"
printf "######### preonic ########\n"
printf "##########################\n"
cp -r preonic/* ~/qmk_firmware/keyboards/preonic/keymaps/dbeley
qmk compile -kb preonic/rev3 -km dbeley
printf "##########################\n"
printf "######### sofle ##########\n"
printf "##########################\n"
cp -r sofle/* ~/qmk_firmware/keyboards/sofle/keymaps/dbeley
qmk compile -kb sofle -km dbeley
printf "##########################\n"
printf "######### xd75 ###########\n"
printf "##########################\n"
cp -r xd75/* ~/qmk_firmware/keyboards/xd75/keymaps/dbeley
qmk compile -kb xd75 -km dbeley
printf "################################\n"
printf "######### ymdk macropad ########\n"
printf "################################\n"
cp -r ymdk/* ~/qmk_firmware/keyboards/ymdk_np21/keymaps/dbeley
qmk compile -kb ymdk_np21 -km dbeley
