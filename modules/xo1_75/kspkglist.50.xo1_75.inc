olpc-runin-tests

# odd - koji repo claims to have portmidi but it doesn't 
-portmidi

# if your build claims that it can't find it
# you may need to tweak your build host with
#
#   echo armv7l-fedora-linux-gnu > /etc/rpm/platform
kernel.armv7l
