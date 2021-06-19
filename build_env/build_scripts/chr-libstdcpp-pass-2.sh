. $DIST_ROOT/build_env/build_scripts/inc-start.sh $1 $(basename $0)

ln -s gthr-posix.h libgcc/gthr-default.h
mkdir -v build
cd       build
../libstdc++-v3/configure            \
    CXXFLAGS="-g -O2 -D_GNU_SOURCE"  \
    --prefix=/usr                    \
    --disable-multilib               \
    --disable-nls                    \
    --host=$(uname -m)-lfs-linux-gnu \
    --disable-libstdcxx-pch

make && make install

. $DIST_ROOT/build_env/build_scripts/inc-end.sh $1 $(basename $0)
