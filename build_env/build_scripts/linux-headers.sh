echo 
echo "Linux Headers"
echo
sleep 1

cd $LFS/sources
tar -xf linux-5.10.17.tar.xz
cd linux-5.10.17

make mrproper

make headers
find usr/include -name '.*' -delete
rm usr/include/Makefile
cp -rv usr/include $LFS/usr

cd $LFS/sources
rm -rf linux-5.10.17

