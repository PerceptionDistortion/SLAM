cmake_minimum_required(VERSION 3.8)
project(dataset_player)

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
    cv_bridge
    image_transport

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
    TARGETS dataset_player

    EXPORT export_dataset_player

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

############################################################
# Export
############################################################

ament_export_targets(export_dataset_player HAS_LIBRARY_TARGET)

ament_export_include_directories(include)

ament_export_dependencies(

    rclcpp

    sensor_msgs
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