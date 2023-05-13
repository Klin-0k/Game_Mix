#Base
cmake_minimum_required(VERSION 3.16)
project(TP_2023_Project)
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/exe)
if (WIN32)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif(WIN32)
if (UNIX)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux_lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux_lib)
endif (UNIX)
#add_library(Global_Classes Global_Classes.cpp Global_Classes.h)
add_executable(${PROJECT_NAME} main.cpp Global_Definitions.h Resources/icons/i.rc)
#target_link_libraries(${PROJECT_NAME} Global_Classes)
add_definitions(-DPATH_TO_PROJECT_FILES="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPATH_TO_RESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
##########################################################################
include(ExternalProject)

if (WIN32)
#  if (NOT EXISTS ./SFML-2.5.1)
#    ExternalProject_Add(
#            SFML-2.5.1
#            URL https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
#            PREFIX ./
#            CONFIGURE_COMMAND ""
#            BUILD_COMMAND ""
#            INSTALL_COMMAND ${CMAKE_COMMAND} -E tar xf ./SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip ./
#            COMMAND ${CMAKE_COMMAND} -E remove ./SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
#    )
#    add_dependencies(${PROJECT_NAME}, SFML-2.5.1)
#    add_dependencies(SFML, SFML-2.5.1)
#  endif (NOT EXISTS ./SFML-2.5.1)
  set(SFML ./SFML-2.5.1)
  set(SFML_DIR ${SFML}/lib/cmake/SFML)
  set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
  set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)
if (UNIX)
  if (NOT EXISTS ./SFML-2.5.1_for_linux)

  endif (NOT EXISTS ./SFML-2.5.1_for_linux)
  set(SFML ./SFML-2.5.1_for_linux)
  set(SFML_DIR ${SFML}/lib/cmake/SFML)
endif (UNIX)
#target_link_libraries(Global_Classes sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
find_package(SFML REQUIRED graphics network audio window system)
##########################################################################

set(DEBUG 0)

add_subdirectory(tests)