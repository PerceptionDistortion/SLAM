#pragma once

#include <memory>
#include <vector>

#include "dataset_driver/sensor_raw_data/RawSensorData.hpp"

class SensorDataBundle
{
public:
    SensorDataBundle() = default;

    void addData(const std::shared_ptr<RawSensorData>& data);

    void clear();

    bool empty() const;

    std::size_t size() const;

    const std::vector<std::shared_ptr<RawSensorData>>& getData() const;

private:
    std::vector<std::shared_ptr<RawSensorData>> sensorData_;
};
