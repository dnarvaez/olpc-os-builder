# Copyright (C) 2009 One Laptop Per Child
# Licensed under the terms of the GNU GPL v2 or later; see COPYING for details.

. $OOB__shlib

oIFS=$IFS
IFS=$'\n'
BADSCRIPT='false'
for line in $(env); do
	[[ "${line:0:34}" == "CFG_custom_scripts__custom_script_" ]] || continue
	script=${line#*=}
	if [ ! -x $script ]; then
	    BADSCRIPT='yes'
	    echo "$script is not executable" 
	fi
done
if [ "$BADSCRIPT" = 'yes' ];then
    exit 1
fi
IFS=$oIFS
