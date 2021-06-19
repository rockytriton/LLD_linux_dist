. $DIST_ROOT/build_env/build_scripts/inc-start.sh $1 $(basename $0)

mkdir -v build
cd       build

../configure                   \
    --prefix=/usr              \
    --build=$(../config.guess) \
    --host=$LFS_TGT            \
    --disable-nls              \
    --enable-shared            \
    --disable-werror           \
    --enable-64-bit-bfd

make
make DESTDIR=$LFS install
install -vm755 libctf/.libs/libctf.so.0.0.0 $LFS/usr/lib


. $DIST_ROOT/build_env/build_scripts/inc-end.sh $1 $(basename $0)
