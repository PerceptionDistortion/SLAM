cmake_minimum_required(VERSION 3.8)

project(dataset_driver)

#################################################
# C++
#################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#################################################
# Dependencies
#################################################

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

find_package(yaml-cpp REQUIRED)

#################################################
# Executable
#################################################

add_executable(dataset_driver_node
    # Add .cpp files here as you implement them

    src/datasets/EurocDatasetDriver.cpp
    # src/datasets/DatasetPlayer.cpp

    src/SensorManager.cpp

    # src/sensor_buffers/CameraBuffer.cpp
    # src/sensor_buffers/IMUBuffer.cpp
    # src/sensor_buffers/LidarBuffer.cpp

    src/sensor_definition/Sensor.cpp
    # src/sensor_definition/CameraSensor.cpp
    # src/sensor_definition/IMUSensor.cpp

    # src/sensor_raw_data/CameraRawData.cpp
    # src/sensor_raw_data/IMURawData.cpp
)

target_include_directories(dataset_driver_node
    PRIVATE
        include
)

ament_target_dependencies(
    dataset_driver_node

    rclcpp
    sensor_msgs
    cv_bridge
    image_transport
)

target_link_libraries(
    dataset_driver_node

    Eigen3::Eigen
    ${OpenCV_LIBS}
    yaml-cpp
)

#################################################
# Install
#################################################

install(
    TARGETS
        dataset_driver_node

    DESTINATION
        lib/${PROJECT_NAME}
)

install(
    DIRECTORY
        include/

    DESTINATION
        include
)

install(
    DIRECTORY
        launch
        config

    DESTINATION
        share/${PROJECT_NAME}
)

#################################################
# Testing
#################################################

if(BUILD_TESTING)

    find_package(ament_lint_auto REQUIRED)

    set(ament_cmake_copyright_FOUND TRUE)
    set(ament_cmake_cpplint_FOUND TRUE)

    ament_lint_auto_find_test_dependencies()

endif()

ament_package()