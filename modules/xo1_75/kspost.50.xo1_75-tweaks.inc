
sed -i -e 's/PROMPT=yes/PROMPT=no/' /etc/sysconfig/init

# Disable package gpg check until F-14 arm repos are signed
sed -i.rpmsave 's/gpgcheck=1/gpgcheck=0/' /etc/yum.repos.d/fedora.repo
sed -i.rpmsave 's/gpgcheck=1/gpgcheck=0/' /etc/yum.repos.d/fedora-updates.repo

mknod /dev/console c 5 1

cat >/home/olpc/.i18n <<__EOF__
LANG="en_US.UTF-8"
__EOF__
chown olpc:olpc /home/olpc/.i18n
