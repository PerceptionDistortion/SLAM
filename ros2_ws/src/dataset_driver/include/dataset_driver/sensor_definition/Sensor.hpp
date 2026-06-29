//Represents a physical sensor that produces data

#pragma once

#include<memory>

#include "dataset_driver/sensor_definition/SensorContext.hpp"
#include"dataset_driver/sensor_buffers/SensorBuffer.hpp"

class Sensor
{
public:
    virtual ~Sensor() = default;

    explicit Sensor(const SensorContext& context);

    const SensorContext& getContext() const;

protected:
    SensorContext context_;
    std::shared_ptr<SensorBuffer> buffer_;
};