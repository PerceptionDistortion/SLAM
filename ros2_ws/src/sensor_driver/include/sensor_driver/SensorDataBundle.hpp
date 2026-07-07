#pragma once

#include <memory>
#include <vector>

#include "sensor_driver/raw_sensor_data/RawSensorData.hpp"

class SensorDataBundle
{
public:

    SensorDataBundle() = default;

    /// Add one sensor measurement to the bundle.
    void addData(const std::shared_ptr<RawSensorData>& data);

    /// Remove all measurements.
    void clear();

    /// Returns true if the bundle contains no measurements.
    bool empty() const;

    /// Number of measurements in the bundle.
    std::size_t size() const;

    /// Access all measurements.
    const std::vector<std::shared_ptr<RawSensorData>>&
    getData() const;

private:

    std::vector<std::shared_ptr<RawSensorData>> sensorData_;
};