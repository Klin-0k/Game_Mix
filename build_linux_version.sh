if ! [ -d ./SFML-2.5.1_for_linux ]; then
  wget https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz
  mkdir SFML-2.5.1_for_linux
  tar -xzf SFML-2.5.1-linux-gcc-64-bit.tar.gz -C ./SFML-2.5.1_for_linux
  mv SFML-2.5.1_for_linux/SFML-2.5.1/* SFML-2.5.1_for_linux
  rm -r SFML-2.5.1_for_linux/SFML-2.5.1
  rm SFML-2.5.1-linux-gcc-64-bit.tar.gz
fi
cd test
curl -LO 'https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip'
unzip v1.13.0.zip
rm v1.13.0.zip
cd ..
#if command -v apt &> /dev/null; then
#  apt-get update
#  apt-get install libgtest-dev
#  apt-get install libgmock-dev
#elif command -v apk &> /dev/null; then
#  apk add libgtest-dev
#  apk add libgmock-dev
#fi
if [ -d ./linux_bush_build ]; then
  rm -r ./linux_bush_build
fi
mkdir ./linux_bush_build
cd ./linux_bush_build
cmake ..
make
cd ..