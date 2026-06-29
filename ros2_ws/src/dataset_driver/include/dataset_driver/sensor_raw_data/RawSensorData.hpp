#pragma once

#include "dataset_driver/sensor_definition/SensorContext.hpp"

class RawSensorData{
    public:
    //Destructor
    virtual ~RawSensorData() = default;

    //Constructors
    RawSensorData() = default;
    RawSensorData(const SensorContext& context, double timestamp)
        : context(context),timestamp(timestamp){}

    /// Sensor that produced this measurement.
    SensorContext context;

    /// Timestamp in seconds.
    double timestamp = 0.0;
    private:
};