# FIXME: old olpc.fth looks for olpcrd.img, but we now use initrd.img
# any nicer way to fix this?
[ -e "/boot/olpcrd.img" ] || ln -s initrd.img /boot/olpcrd.img

# olpc.fth really shouldnt specify a root device or filesystem, the initramfs
# figures this out (like in the signed boot path).
# FIXME: fix bootfw package
# sed -i -e 's:root=mtd0 rootfstype=jffs2::g' /boot/olpc.fth

# do not show the Sugar default ad-hoc networks on the XO-1
gconftool-2 --direct --config-source xml:readwrite:/etc/gconf/gconf.xml.defaults --type bool --set /desktop/sugar/network/adhoc false

# add /ofw, can be removed when we move to newer kernels with /proc/device-tree
mkdir /ofw
echo "none            /ofw            promfs		  defaults    0 0" >> /etc/fstab

# Temporary workaround to #11214 transition
cat <<'EOF' > /boot/olpc.fth
\ OLPC boot script

[ifndef] do-firmware-update

: do-firmware-update  ( img$ -- )

\ Keep .error from printing an input sream position report
\ which makes a buffer@<address> show up in the error message
  ['] noop to show-error

  visible

   tuck flash-buf  swap move   ( len )

   ['] ?image-valid  catch  ?dup  if    ( )
      visible
      red-letters
      ." Bad firmware image file - "  .error
      ." Continuing with old firmware" cr
      black-letters
      exit
   then

   true to file-loaded?

   d# 12,000 wait-until   \ Wait for EC to notice the battery

   ['] ?enough-power  catch  ?dup  if
      visible
      red-letters
      ." Unsafe to update firmware now - " .error
      ."  Continuing with old firmware" cr
      black-letters
      exit
   then

   " Updating firmware" ?lease-debug-cr

   ec-indexed-io-off?  if
      visible
      ." Restarting to enable SPI FLASH writing."  cr
      d# 3000 ms
      ec-ixio-reboot
      security-failure
   then

   \ Latch alternate? flag for next startup
   alternate?  if  [char] A h# 82 cmos!  then

   reflash      \ Should power-off and reboot
   show-x
   " Reflash returned, unexpectedly" .security-failure
;

[then]

[ifndef] ?ofw-reflash
\ Check for new firmware.
: ?ofw-reflash  ( -- )
   " ${DN}${PN}\bootfw.zip" expand$
   ['] (boot-read) catch  if  2drop exit  then
   img$  firmware-up-to-date?  if  exit  then
   img$ do-firmware-update
;

[then]

: set-path-macros  ( -- )
   button-o game-key?  if  " \boot-alt"  else  " \boot"  then  pn-buf place

   " /chosen" find-package  if                       ( phandle )
      " bootpath" rot  get-package-property  0=  if  ( propval$ )
         get-encoded-string                          ( bootpath$ )
         [char] \ left-parse-string  2nip            ( dn$ )
         dn-buf place                                ( )
      then
   then

   " nand"  dn-buf count  sindex  0>=   if
      " "
   else
      " root=LABEL=OLPCRoot rootfstype=ext3"
   then
   " ROOTDEV" $set-macro
;

: olpc-fth-boot-me
   set-path-macros
   ?ofw-reflash
   " ro ${ROOTDEV} console=ttyS0,115200 console=tty0 fbcon=font:SUN12x22" expand$ to boot-file
   " ${DN}${PN}\vmlinuz"    expand$ to boot-device
   " ${DN}${PN}\olpcrd.img" expand$ to ramdisk
   boot
;
olpc-fth-boot-me
EOF
