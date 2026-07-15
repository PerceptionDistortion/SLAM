cmake_minimum_required(VERSION 3.8)
project(dataset_player)

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

find_package(sensor_driver REQUIRED)

############################################################
# Library
############################################################

add_library(dataset_player

    src/DatasetPlayerNode.cpp

    src/publishers/PublisherManager.cpp
    src/publishers/CameraPublisher.cpp
    src/publishers/ImuPublisher.cpp
)

target_include_directories(dataset_player
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(dataset_player

    Eigen3::Eigen

    ${OpenCV_LIBS}
)

ament_target_dependencies(dataset_player

    rclcpp

    sensor_msgs
    std_msgs
    cv_bridge
    image_transport

    sensor_driver
)

############################################################
# Executable
############################################################

add_executable(dataset_player_node
    src/main.cpp
)

target_link_libraries(dataset_player_node
    dataset_player
)

ament_target_dependencies(dataset_player_node

    rclcpp

    sensor_driver
)

############################################################
# Install
############################################################

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
)

install(
    DIRECTORY config
    DESTINATION share/${PROJECT_NAME}
)

install(
    TARGETS

        dataset_player
        dataset_player_node

    EXPORT export_dataset_player

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)

############################################################
# Export
############################################################

ament_export_targets(
    export_dataset_player
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

    sensor_driver
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