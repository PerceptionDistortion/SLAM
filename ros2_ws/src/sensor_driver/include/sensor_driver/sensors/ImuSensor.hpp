#pragma once

#include "Sensor.hpp"

class ImuSensor : public Sensor
{
public:

    explicit ImuSensor(const SensorContext& context): Sensor(context){}

public:

    double gyroNoise = 0.0;
    double accelNoise = 0.0;
};