#pragma once

#include<string>

#include "sensor_driver/sensors/SensorType.hpp"

struct SensorContext{

    std::string id; //cam0, cam1, imu0, etc.

    SensorType type; //enum

    //in ROS or actual robots, we need a physical sensor correspondence
    //E.g. frameID="left hand camera"
    std::string frameID;

    double frequency=0.0;

    bool enabled=true;
};