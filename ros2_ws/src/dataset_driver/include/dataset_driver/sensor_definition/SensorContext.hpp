//All sensor specific data
//Generic: will not be extended for each sensor

#pragma once

#include<string>

#include "dataset_driver/SensorType.hpp"

struct SensorContext
{
    std::string id;          // "cam0", "imu0", "lidar_front"
    SensorType type;

    //This is related to robotic or ROS2 links, not dataset frames
    std::string frameId;
    
    double frequency = 0.0;
    bool enabled = true;
};