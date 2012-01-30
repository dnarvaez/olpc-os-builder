# add /ofw, can be removed when we move to newer kernels with /proc/device-tree
mkdir /ofw
echo "none            /ofw            promfs		  defaults    0 0" >> /etc/fstab

# Workaround an unknown bug where TamTam sound is crackly on XO-1.5 (#9414)
sed -i -e 's/dmix.rate 48000/dmix.rate 44100/' /usr/share/alsa/alsa.conf

