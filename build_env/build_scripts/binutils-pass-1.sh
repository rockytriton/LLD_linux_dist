cd $LFS/sources
tar -xf binutils-2.36.1.tar.xz
cd binutils-2.36.1

mkdir -v build
cd       build

../configure --prefix=$LFS/tools       \
             --with-sysroot=$LFS        \
             --target=$LFS_TGT          \
             --disable-nls              \
             --disable-werror

make && make install

cd $LFS/sources

rm -rf binutils-2.36.1

