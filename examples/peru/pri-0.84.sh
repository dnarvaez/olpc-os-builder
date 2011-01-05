#!/bin/sh

##################CAMBIOS EN SUGAR##########################

#Cambiar las traducciones
#cp -f /home/aliosh/src/custom/0.84/lang/sugar-toolkit.mo "$INSTALL_ROOT"/usr/share/locale/es/LC_MESSAGES/sugar-toolkit.mo
cp -f /home/aliosh/src/xo-peru/custom/0.84/lang/sugar.mo "$INSTALL_ROOT"/usr/share/locale/es/LC_MESSAGES/sugar.mo

#patch para vnc
patch -p0 "$INSTALL_ROOT"/etc/X11/xorg-dcon.conf /home/aliosh/src/xo-peru/custom/x11/enablextest.patch
sed -i -e '3d'  "$INSTALL_ROOT"/etc/issue
echo "Personalizado para PERU por:"  >> "$INSTALL_ROOT"/etc/issue
echo "Aliosh Neira(aliosh2006@gmail.com) y Hernan Pachas(hernan.pachas@gmail.com)" >> "$INSTALL_ROOT"/etc/issue
echo -e "\n" >> "$INSTALL_ROOT"/etc/issue

#ajuste puntero touchpad

echo 'xset m 5 1' >> "$INSTALL_ROOT"/home/olpc/.xsession

