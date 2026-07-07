#pragma once

#include <opencv2/core.hpp>

#include "sensor_driver/sensors/Sensor.hpp"

class CameraSensor : public Sensor
{
public:
    explicit CameraSensor(const SensorContext& context): Sensor(context){}

public:

    cv::Mat K;
    cv::Mat D;

    //Image resolution of camera
    int width = 0;
    int height = 0;
};