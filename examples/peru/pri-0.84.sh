#!/bin/bash -x

set -e

##################CAMBIOS EN SUGAR##########################

CONFDIR=/home/martin/src/olpc-os-builder/examples/peru
for F in sugar sugar-toolkit; do
    # extract
    msgunfmt "$INSTALL_ROOT"/usr/share/locale/es/LC_MESSAGES/$F.mo > /tmp/$F-orig.po
    # merge with new definitions
    msgmerge $CONFDIR/$F.po /tmp/$F-orig.po > /tmp/$F-new.po
    # compile & install 
    msgfmt /tmp/$F-new.po > "$INSTALL_ROOT"/usr/share/locale/es/LC_MESSAGES/$F.mo
done

#patch para vnc
#patch -p0 "$INSTALL_ROOT"/etc/X11/xorg-dcon.conf /home/aliosh/src/xo-peru/custom/x11/enablextest.patch

# chop the empty line in /etc/issue
sed -i -e '3d'  "$INSTALL_ROOT"/etc/issue
# Add credits
echo "Personalizado para PERU por:"  >> "$INSTALL_ROOT"/etc/issue
echo "Aliosh Neira(aliosh2006@gmail.com) y Hernan Pachas(hernan.pachas@gmail.com)" >> "$INSTALL_ROOT"/etc/issue
echo -e "\n" >> "$INSTALL_ROOT"/etc/issue


#ajuste puntero touchpad
echo 'xset m 5 1' >> "$INSTALL_ROOT"/home/olpc/.xsession

