cmake_minimum_required(VERSION 3.16)
project(exercise1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui videoio)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(exercise1 src/main.cpp src/data_loader.cpp)
target_link_libraries(exercise1 PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)
target_compile_options(exercise1 PRIVATE -Wall -Wextra)

# Absolute path to the exercise data, so the program runs from any working directory
target_compile_definitions(exercise1 PRIVATE
  DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../exercise/Exercise 1 - Augmented Reality Wireframe Cube/data")
