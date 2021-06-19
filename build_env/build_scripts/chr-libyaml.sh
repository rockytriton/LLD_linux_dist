FILE=$1

echo 
echo "Processing $(basename $0)"
echo
sleep 1

cd $LFS/sources
echo "Extracting..."
tar -xf $FILE
DIR=libyaml-0.2.4
cd $DIR
echo "Changed to build path"
pwd

./bootstrap                                &&
./configure --prefix=/usr --disable-static &&
make
make install

echo
echo "Cleaning up..."
echo

cd $LFS/sources
rm -rf $DIR

echo
echo "Done Processing $(basename $0)"
echo
