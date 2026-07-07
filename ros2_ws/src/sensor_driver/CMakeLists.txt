cmake_minimum_required(VERSION 3.8)
project(sensor_driver)

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

############################################################
# Header-only library
############################################################

add_library(sensor_driver INTERFACE)

target_include_directories(sensor_driver
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sensor_driver
INTERFACE
    Eigen3::Eigen
    ${OpenCV_LIBS}
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
)

############################################################
# Export
############################################################

ament_export_targets(export_sensor_driver HAS_LIBRARY_TARGET)

ament_export_include_directories(include)

ament_export_dependencies(
    rclcpp
    sensor_msgs
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