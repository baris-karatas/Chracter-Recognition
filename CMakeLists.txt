cmake_minimum_required(VERSION 3.17)
project(Character_recog)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR /Users/blackstone/opencv/opencv/build)


find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})



add_executable(Character_recog main.cpp)
target_link_libraries(Character_recog ${OpenCV_LIBS} )