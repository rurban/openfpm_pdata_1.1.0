#! /bin/bash

# check if the directory $1/EIGEN exist

if [ -d "$1/EIGEN" ]; then
  echo "EIGEN is already installed"
  exit 0
fi

./script/install_OPENBLAS.sh $1 $2
if [ ! -d "$1/OPENBLAS"  ]; then
  exit 1
fi

CXX="$CXX" CC="$CC" FC="$FC" F77="$F77" ./script/install_SUITESPARSE.sh $1 $2
if [ ! -d "$1/SUITESPARSE"  ]; then
  exit 1
fi

wget http://ppmcore.mpi-cbg.de/upload/eigen-3.3.1.tar.bz2
rm -rf eigen-eigen-f562a193118d
tar -xf eigen-3.3.1.tar.bz2

cd eigen-eigen-f562a193118d
mkdir $1/EIGEN/
mv Eigen $1/EIGEN/Eigen

cd ..
rm -rf eigen-eigen-f562a193118d

# Mark the installation
echo 1 > $1/EIGEN/version
