#pragma once

#include <filesystem>

#include"sensor_driver/sensors/CameraSensor.hpp"
#include"sensor_driver/sensors/ImuSensor.hpp"

class Calibration
{
public:

    virtual ~Calibration() = default;
    virtual bool calibrate(CameraSensor& sensor) = 0;
    virtual bool calibrate(ImuSensor& sensor) = 0;
};