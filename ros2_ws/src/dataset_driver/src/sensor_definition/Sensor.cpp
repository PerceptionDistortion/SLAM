#include "dataset_driver/sensor_definition/Sensor.hpp"

Sensor::Sensor(const SensorContext& context)
    : context_(context)
{
}

const SensorContext& Sensor::getContext() const
{
    return context_;
}