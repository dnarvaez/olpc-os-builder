# make batti start automatically (#10436)
if [ -e /usr/share/applications/batti.desktop ]; then
    mv /usr/share/applications/batti.desktop /etc/xdg/autostart
fi
