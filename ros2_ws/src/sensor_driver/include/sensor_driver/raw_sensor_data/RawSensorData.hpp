#pragma once

#include<memory>

#include "sensor_driver/sensors/Sensor.hpp"

class RawSensorData
{
public:

    RawSensorData(std::shared_ptr<Sensor> sensor,double timestamp):
        sensor_(sensor),timestamp_(timestamp){}

    virtual ~RawSensorData() = default;

    //Getters for sensor and the timestamp
    std::shared_ptr<Sensor> sensor() const
    {
        return sensor_;
    }

    double timestamp() const
    {
        return timestamp_;
    }

protected:

    std::shared_ptr<Sensor> sensor_;

    double timestamp_;
};