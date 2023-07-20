cmake_minimum_required(VERSION 3.16)

project(Test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
add_executable(Test main.cpp)
target_link_libraries(Test gtest_main gmock_main)
set(SFML ../SFML)
set(SFML_DIR ${SFML}/lib/cmake/SFML)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
find_package(SFML REQUIRED graphics network audio window system)