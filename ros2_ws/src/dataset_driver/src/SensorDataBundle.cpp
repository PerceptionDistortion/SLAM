#include "dataset_driver/SensorDataBundle.hpp"

void SensorDataBundle::addData(
    const std::shared_ptr<RawSensorData>& data)
{
    sensorData_.push_back(data);
}

void SensorDataBundle::clear()
{
    sensorData_.clear();
}

bool SensorDataBundle::empty() const
{
    return sensorData_.empty();
}

std::size_t SensorDataBundle::size() const
{
    return sensorData_.size();
}

const std::vector<std::shared_ptr<RawSensorData>>&
SensorDataBundle::getData() const
{
    return sensorData_;
}
