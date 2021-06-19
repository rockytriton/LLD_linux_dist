
echo "Entering Chroot: ${LFS:?}"

bash -e $DIST_ROOT/build_env/build_scripts/mount-virt.sh

chroot "$LFS" /usr/bin/env -i   \
    HOME=/root                  \
    TERM="$TERM"                \
    PS1='(lfs chroot) \u:\w\$ ' \
    PATH=/bin:/usr/bin:/sbin:/usr/sbin \
    /bin/bash --login +h

bash -e $DIST_ROOT/build_env/build_scripts/umount-virt.sh
