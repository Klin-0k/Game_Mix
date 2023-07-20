#!/bin/sh

if ! [ -d ./SFML ]; then
  curl -LO https://www.sfml-dev.org/files/SFML-2.6.1-sources.zip
  unzip SFML-2.6.1-sources.zip
  mkdir SFML
  cd SFML-2.6.1
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX=../../SFML ..
  make install
  cd ../..
  mkdir SFML/Frameworks
  mv SFML/lib/*framework* SFML/Frameworks
  rm -r SFML-2.6.1
  rm SFML-2.6.1-sources.zip
fi

if ! [ -d ./tests/googletest ]; then
cd tests
curl -LO 'https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip'
unzip v1.13.0.zip
rm v1.13.0.zip
mv ./googletest-1.13.0 ./googletest
cd ..
fi

if [ -d ./build ]; then
  rm -r ./build
fi
mkdir ./build
cd ./build
cmake ..
make
cd ..