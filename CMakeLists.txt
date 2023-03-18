#Base
cmake_minimum_required(VERSION 3.23)
project(TP_2023_Project)
set(CMAKE_CXX_STANDARD 23)
add_executable(TP_2023_Project main.cpp Global_Variables.h)
##########################################################################


#Useless magic?
#include_directories(${SFML-2.5.1}/include)
#link_directories(${SFML-2.5.1}/lib)
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
##########################################################################


#some magic that turn on SFML
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML-2.5.1 ./SFML-2.5.1)
set(SFML_DIR ${SFML-2.5.1}/lib/cmake/SFML)
target_link_libraries(TP_2023_Project sfml-graphics sfml-window sfml-system)
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)
##########################################################################

