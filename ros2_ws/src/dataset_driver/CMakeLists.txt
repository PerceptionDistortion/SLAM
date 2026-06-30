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

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)

#################################################
# Library
#################################################

add_library(${PROJECT_NAME}

    #################################################
    # Dataset Drivers
    #################################################

    src/datasets/EurocDatasetDriver.cpp

    #################################################
    # Managers
    #################################################

    src/SensorManager.cpp
    src/SensorDataBundle.cpp

    #################################################
    # Sensor Definitions
    #################################################

    src/sensor_definition/Sensor.cpp

    #################################################
    # Add more cpp files here as they are implemented
    #################################################

    # src/sensor_definition/CameraSensor.cpp
    # src/sensor_definition/IMUSensor.cpp
    # src/sensor_definition/LidarSensor.cpp

    # src/sensor_raw_data/CameraRawData.cpp
    # src/sensor_raw_data/IMURawData.cpp
    # src/sensor_raw_data/LidarRawData.cpp
)

#################################################
# Include Directories
#################################################

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

#################################################
# Link Libraries
#################################################

target_link_libraries(${PROJECT_NAME}

    Eigen3::Eigen
    ${OpenCV_LIBS}
    yaml-cpp
)

#################################################
# Install
#################################################

install(
    TARGETS ${PROJECT_NAME}

    EXPORT export_${PROJECT_NAME}

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY include/

    DESTINATION include
)

install(
    EXPORT export_${PROJECT_NAME}

    FILE ${PROJECT_NAME}Targets.cmake

    NAMESPACE ${PROJECT_NAME}::

    DESTINATION share/${PROJECT_NAME}/cmake
)

install(
    DIRECTORY
        config

    DESTINATION
        share/${PROJECT_NAME}
)

#################################################
# Export
#################################################

ament_export_include_directories(include)

ament_export_targets(export_${PROJECT_NAME})

ament_export_dependencies(
    OpenCV
    Eigen3
    yaml-cpp
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