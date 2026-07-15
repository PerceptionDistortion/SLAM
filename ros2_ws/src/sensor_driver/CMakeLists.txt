cmake_minimum_required(VERSION 3.8)
project(sensor_driver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR
   CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

############################################################
# Dependencies
############################################################

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)

find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)

############################################################
# Library
############################################################

add_library(sensor_driver

    src/SensorManager.cpp
    src/SensorDataBundle.cpp

    src/calibration/EurocCalibration.cpp

    src/sensor_drivers/EurocDatasetDriver.cpp
)

target_include_directories(sensor_driver
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sensor_driver

    Eigen3::Eigen

    ${OpenCV_LIBS}

    yaml-cpp
)

ament_target_dependencies(sensor_driver

    rclcpp

    sensor_msgs
    std_msgs
    cv_bridge
    image_transport
)

############################################################
# Install
############################################################

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    TARGETS sensor_driver

    EXPORT export_sensor_driver

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

############################################################
# Export
############################################################

ament_export_targets(
    export_sensor_driver
    HAS_LIBRARY_TARGET
)

ament_export_include_directories(include)

ament_export_dependencies(

    rclcpp

    sensor_msgs
    std_msgs
    cv_bridge
    image_transport

    Eigen3
    OpenCV
)

############################################################
# Testing
############################################################

if(BUILD_TESTING)

    find_package(ament_lint_auto REQUIRED)

    set(ament_cmake_copyright_FOUND TRUE)
    set(ament_cmake_cpplint_FOUND TRUE)

    ament_lint_auto_find_test_dependencies()

endif()

ament_package()