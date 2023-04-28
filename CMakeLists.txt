#Base
cmake_minimum_required(VERSION 3.16)
project(TP_2023_Project)
set(CMAKE_CXX_STANDARD 20)
#add_library(Global_Classes Global_Classes.cpp Global_Classes.h)
add_executable(${PROJECT_NAME} main.cpp Global_Variables.h)
#target_link_libraries(${PROJECT_NAME} Global_Classes)
add_definitions(-DPATH_TO_PROJECT_FILES="${CMAKE_CURRENT_SOURCE_DIR}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

##########################################################################



#Useless magic?
#if (WIN32)
#    set(RC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Resources/i.rc")
#    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "")
#endif()
##########################################################################
#include_directories(${SFML-2.5.1}/include)
#link_directories(${SFML-2.5.1}/lib)
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
##########################################################################


#some magic that turn on SFML
if (WIN32)
  set(SFML ./SFML-2.5.1)
  set(SFML_DIR ${SFML}/lib/cmake/SFML)
  set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
  set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

if (UNIX)
  set(SFML ./SFML-2.5.1_for_linux)
  set(SFML_DIR ${SFML}/lib/cmake/SFML)
endif (UNIX)
#target_link_libraries(Global_Classes sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
find_package(SFML REQUIRED graphics network audio window system)
##########################################################################

