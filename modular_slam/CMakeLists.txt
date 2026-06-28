cmake_minimum_required(VERSION 3.16)

project(ModularSLAM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)

add_executable(
    ModularSLAM
    facade/main.cpp
)

target_include_directories(
    ModularSLAM
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ModularSLAM
    PRIVATE
    ${OpenCV_LIBS}
    Eigen3::Eigen
    Ceres::ceres
)