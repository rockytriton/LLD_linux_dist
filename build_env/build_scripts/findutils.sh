. $DIST_ROOT/build_env/build_scripts/inc-start.sh $1 $(basename $0)

./configure --prefix=/usr   \
            --host=$LFS_TGT \
            --build=$(build-aux/config.guess)

make && make DESTDIR=$LFS install

mv -v $LFS/usr/bin/find $LFS/bin
sed -i 's|find:=${BINDIR}|find:=/bin|' $LFS/usr/bin/updatedb

. $DIST_ROOT/build_env/build_scripts/inc-end.sh $1 $(basename $0)
