cat > /boot/olpc.fth <<EOF
\ olpc.fth
d4282c08 l@ 80.0000 invert and d4282c08 l!
load ext:\zImage
go
EOF

cat > /etc/X11/xorg.conf <<EOF
Section "Device"
	Identifier	"Configured Video Device" 
	Option		"UseFBDev"		"true"
	Option		"ShadowFB"		"true"
	Option		"fbdev"			"/dev/fb0"
	Driver		"fbdev"
EndSection

Section "Module"
	Disable "glx"
EndSection

Section "Extensions"
	Option "Composite" "False"
EndSection

Section "ServerLayout"
	Identifier "layout"
	Option "Damage" "False"
EndSection
EOF

cat >> /etc/rc.local <<EOF
date 121517002010
agetty /dev/ttyS2 115200 &
EOF

sed -i -e 's/PROMPT=yes/PROMPT=no/' /etc/sysconfig/init
