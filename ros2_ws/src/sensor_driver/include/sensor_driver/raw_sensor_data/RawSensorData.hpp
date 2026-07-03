#pragma once

#include<memory>

#include"sensors/Sensor.hpp"

class RawSensorData
{
public:

    RawSensorData(std::shared_ptr<Sensor> sensor,double timestamp):
        sensor_(sensor),timestamp_(timestamp){}

    virtual ~RawSensorData() = default;

protected:

    std::shared_ptr<Sensor> sensor_;

    double timestamp_;
};