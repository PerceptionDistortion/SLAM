#pragma once

#include"Sensor.hpp"

class CameraSensor : public Sensor
{
public:
    using Sensor::Sensor;

    cv::Mat K;
    cv::Mat D;

    int width;
    int height;
};