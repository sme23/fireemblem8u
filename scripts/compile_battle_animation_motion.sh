#!/bin/bash

# compile battle animation to object -> dump separate binaries -> lz77 compress
# including modes, script, oam_r, oam_l

cd banim

if [ $# -eq 0 ]
then
    PATH=$PATH:$DEVKITARM:$DEVKITPRO
    echo $PATH
    as=arm-none-eabi-as
    objcopy=arm-none-eabi-objcopy
else
    as=$1
    objcopy=$2
fi

ls | grep '_motion.s' | while read f_motion
do
    f_base=${f_motion%motion.s}
    $as $f_motion -o $f_base'motion.o'
    $objcopy -O binary --dump-section .data.modes=$f_base"modes.bin" --dump-section .data.script=$f_base"script.bin" --dump-section .data.oam_r=$f_base"oam_r.bin" --dump-section .data.oam_l=$f_base"oam_l.bin" $f_base"motion.o" $f_base"motion.bin"
    ../tools/gbagfx/gbagfx $f_base"script.bin" $f_base"script.bin.lz"
    ../tools/gbagfx/gbagfx $f_base"oam_r.bin" $f_base"oam_r.bin.lz"
    ../tools/gbagfx/gbagfx $f_base"oam_l.bin" $f_base"oam_l.bin.lz"
done
cd -
