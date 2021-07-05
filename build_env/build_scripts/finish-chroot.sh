#!/bin/bash

set -e

mkdir -pv /{boot,home,mnt,opt,srv}
mkdir -pv /etc/{opt,sysconfig}
mkdir -pv /lib/firmware
mkdir -pv /media/{floppy,cdrom}
mkdir -pv /usr/{,local/}{bin,include,lib,sbin,src}
mkdir -pv /usr/{,local/}share/{color,dict,doc,info,locale,man}
mkdir -pv /usr/{,local/}share/{misc,terminfo,zoneinfo}
mkdir -pv /usr/{,local/}share/man/man{1..8}
mkdir -pv /var/{cache,local,log,mail,opt,spool}
mkdir -pv /var/lib/{color,misc,locate}

ln -sfv /run /var/run
ln -sfv /run/lock /var/lock

install -dv -m 0750 /root
install -dv -m 1777 /tmp /var/tmp

ln -sfv /proc/self/mounts /etc/mtab
echo "127.0.0.1 localhost lldos" > /etc/hosts

touch /var/log/{btmp,lastlog,faillog,wtmp}
chgrp -v utmp /var/log/lastlog
chmod -v 664  /var/log/lastlog
chmod -v 600  /var/log/btmp

#Start building other packages!
export DIST_ROOT=/dist
cd $DIST_ROOT/build_env

bash -e build_scripts/chr-libstdcpp-pass-2.sh gcc-10.2.0.tar.xz
bash -e build_scripts/chr-gettext.sh gettext-0.21.tar.xz
bash -e build_scripts/chr-bison.sh bison-3.7.5.tar.xz
bash -e build_scripts/chr-perl.sh perl-5.32.1.tar.xz
bash -e build_scripts/chr-python.sh Python-3.9.2.tar.xz
bash -e build_scripts/chr-texinfo.sh texinfo-6.7.tar.xz
bash -e build_scripts/chr-util-linux.sh util-linux-2.36.2.tar.xz

echo "Finished Chroot build!"

find /usr/{lib,libexec} -name \*.la -delete
rm -rf /usr/share/{info,man,doc}/*

exit
