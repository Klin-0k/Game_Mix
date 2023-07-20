#Base
cmake_minimum_required(VERSION 3.16)
project(Game_Mix)
set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/exe)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/arc)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage --coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(MainComp classes/main/Window_class.cpp classes/main/Essence_class.cpp classes/main/Object_class.cpp classes/main/Button_class.cpp classes/main/Fon_class.cpp)
add_library(Menus classes/menus/MainMenu_class.cpp classes/menus/PlayMenu_class.cpp classes/menus/ExitMenu_class.cpp)
add_library(Games classes/games/Game1.cpp classes/games/Game2.cpp)
target_link_libraries(MainComp sfml-graphics sfml-window sfml-system)
target_link_libraries(Menus MainComp)
target_link_libraries(Games Menus)
target_link_libraries(Menus Games)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Games)
add_definitions(-DPATH_TO_PROJECT_FILES="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPATH_TO_RESOURCES="${CMAKE_CURRENT_SOURCE_DIR}/resources")
##########################################################################

set(SFML ./SFML)
set(SFML_DIR ${SFML}/lib/cmake/SFML)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
find_package(SFML REQUIRED graphics network audio window system)
##########################################################################

#add_definitions(-DDEBUG)

add_subdirectory(tests)
target_link_libraries(Test Games)

#add_custom_target(Coverage
#        DEPENDS Test
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#        COMMAND ${EXECUTABLE_OUTPUT_PATH}/Test
#        COMMAND lcov --ignore-errors inconsistent --ignore-errors gcov --capture --directory . --output-file coverage.info
#        COMMAND lcov --ignore-errors inconsistent --remove coverage.info "/usr/include/*" -o coverage.info || true
#        COMMAND lcov --ignore-errors inconsistent --ignore-errors unused --remove coverage.info "tests/*" -o coverage.info || true
#        COMMAND genhtml --ignore-errors inconsistent --ignore-errors unmapped coverage.info --output-directory coverage_report
#)
