# Copyright (C) 2009 One Laptop Per Child
# Licensed under the terms of the GNU GPL v2 or later; see COPYING for details.

# this must be run before the base module creates versioned fs layout

. $OOB__shlib

# FIXME olpc.fth usually comes in the bootfw rpm
cat > $fsmount/boot/olpc.fth <<"EOF"
\ olpc.fth
" root=/dev/mmcblk0p2 console=ttyS2,115200 console=tty0 loglevel=9 rootwait debug" to boot-file
boot last:\vmlinuz

EOF
