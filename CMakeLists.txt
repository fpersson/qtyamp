cmake_minimum_required (VERSION 2.8.11)
project(qtyamp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Network REQUIRED)

set(SOURCE_FILES
    utils/flog.cpp
    utils/flaghandler.cpp
    mediaserver/cmediaplayer.cpp                                                                                                 
    mediaserver/commandparser.cpp
    mediaserver/configreader.cpp
    mediaserver/cserver.cpp
)

add_executable(qtyamp main.cpp ${SOURCE_FILES})

target_link_libraries(qtyamp Qt5::Core Qt5::Network Qt5::Multimedia)