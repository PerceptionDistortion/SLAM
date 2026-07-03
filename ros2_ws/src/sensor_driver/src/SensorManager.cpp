#include "sensor_driver/SensorManager.hpp"

bool SensorManager::registerSensor(const std::shared_ptr<Sensor>& sensor)
{
    if (!sensor) return false;

    const auto& id = sensor->context().id;

    if (hasSensor(id)) return false;

    sensors_[id] = sensor;

    return true;
}

std::shared_ptr<Sensor> SensorManager::getSensor(const std::string& sensorId) const
{
    auto it = sensors_.find(sensorId);

    if (it == sensors_.end())
    {
        return nullptr;
    }

    return it->second;
}

std::vector<std::shared_ptr<Sensor>>SensorManager::getSensors() const
{
    std::vector<std::shared_ptr<Sensor>> sensors;

    sensors.reserve(sensors_.size());

    for (const auto& [id, sensor] : sensors_)
    {
        sensors.push_back(sensor);
    }

    return sensors;
}

bool SensorManager::hasSensor(
    const std::string& sensorId) const
{
    return sensors_.find(sensorId) != sensors_.end();
}

void SensorManager::clear()
{
    sensors_.clear();
}

std::size_t SensorManager::size() const
{
    return sensors_.size();
}

bool SensorManager::empty() const
{
    return sensors_.empty();
}