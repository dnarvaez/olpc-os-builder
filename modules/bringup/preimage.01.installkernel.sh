# Copyright (C) 2009 One Laptop Per Child
# Licensed under the terms of the GNU GPL v2 or later; see COPYING for details.

##
## this script runs in the "preimage" stage, after RPM installation
## and kickstart's %post; right before the base module creates the
## versioned fs layout, and before /bootpart is setup as a copy
## of /boot
##


. $OOB__shlib

kernel_zimage=$(read_config bringup kernel_zimage)
kernel_rpm=$(read_config bringup kernel_rpm)
olpc_fth=$(read_config bringup olpc_fth)
runin_tarball=$(read_config bringup runin_tarball)
overlay=$(read_config bringup overlay)

if [ -n "${kernel_rpm}" ]; then
    #echo "Installing kernel rpm manually..."
    rpm --root "$fsmount" --ignorearch -ivh "${kernel_rpm}"
fi

if [ -n "${kernel_zimage}" ]; then
    rm "$fsmount"/boot/vmlinuz
    cp "${kernel_zimage}" "$fsmount"/boot/vmlinuz
fi

if [ -n "${olpc_fth}" ]; then
    cp "${olpc_fth}" "$fsmount"/boot/olpc.fth
fi

if [ -n "${runin_tarball}" ]; then
    mkdir -p "$fsmount"/boot/runin/
    cp "${runin_tarball}" "$fsmount"/boot/runin/runin.tar.gz
fi

# breaks the build, dunno how
#if [ -n "${overlay}" ]; then
#    # ensure trailing slashes
#    rsync -v --recursive --links "${overlay}"/ "$fsmount"/
#fi

# temporary
touch "$fsmount"/runin/no-camera
touch "$fsmount"/runin/no-suspend

