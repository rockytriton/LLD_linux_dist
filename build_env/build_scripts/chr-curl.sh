. $DIST_ROOT/build_env/build_scripts/inc-start.sh $1 $(basename $0)

grep -rl '#!.*python$' | xargs sed -i '1s/python/&3/'

./configure --prefix=/usr                           \
            --disable-static                        \
            --enable-threaded-resolver              \
            --with-ca-path=/etc/ssl/certs &&
make
make install

. $DIST_ROOT/build_env/build_scripts/inc-end.sh $1 $(basename $0)
