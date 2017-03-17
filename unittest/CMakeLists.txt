cmake_minimum_required(VERSION 2.8)
project(unittest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKEDEMO_SOURCE_DIR}../)
link_directories(${CMAKEDEMO_BINARY_DIR}/)

enable_testing()

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

#add_executable(foo foo.cpp)
set(LIB_SOURCE_FILES ../utils/flog.cpp ../mediaserver/playlistgenerator.cpp)

set(SOURCE_FILES testmain.cpp)
add_executable(unittest ${LIB_SOURCE_FILES} ${SOURCE_FILES})
add_test(unittest unittest)

target_link_libraries(unittest Qt5::Test Qt5::Core)