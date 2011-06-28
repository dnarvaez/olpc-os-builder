
cat >> /etc/rc.local <<EOF
agetty /dev/ttyS2 115200 &
EOF

sed -i -e 's/PROMPT=yes/PROMPT=no/' /etc/sysconfig/init

mknod /dev/console c 5 1

cat >/home/olpc/.i18n <<__EOF__
LANG="en_US.UTF-8"
__EOF__
chown olpc:olpc /home/olpc/.i18n

# temporary workaround for #11008
mv /usr/bin/plymouth{,.disabled}
mv /sbin/plymouthd{,.disabled}
