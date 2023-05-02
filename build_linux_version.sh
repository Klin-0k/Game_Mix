if ! [ -d ./linux_hand_build ]; then
  mkdir ./linux_hand_build
fi
cd ./linux_hand_build
cmake ..
make
cd ..