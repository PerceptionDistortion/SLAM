#include "dataset_driver/SensorManager.hpp"

bool SensorManager::addSensor(const std::shared_ptr<Sensor>& sensor)
{
    if (!sensor)
        return false;

    const std::string& id = sensor->getContext().id;

    if (sensors_.find(id) != sensors_.end())
        return false;

    sensors_[id] = sensor;

    return true;
}

////////////////////////////////////////////////////////////

bool SensorManager::removeSensor(const std::string& sensorId)
{
    return sensors_.erase(sensorId) > 0;
}

////////////////////////////////////////////////////////////

bool SensorManager::hasSensor(const std::string& sensorId) const
{
    return sensors_.find(sensorId) != sensors_.end();
}

////////////////////////////////////////////////////////////

std::shared_ptr<Sensor>
SensorManager::getSensor(const std::string& sensorId) const
{
    auto it = sensors_.find(sensorId);

    if (it == sensors_.end())
        return nullptr;

    return it->second;
}

////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<Sensor>>
SensorManager::getSensors() const
{
    std::vector<std::shared_ptr<Sensor>> result;

    result.reserve(sensors_.size());

    for (const auto& [id, sensor] : sensors_)
    {
        result.push_back(sensor);
    }

    return result;
}

////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<Sensor>>
SensorManager::getSensors(SensorType type) const
{
    std::vector<std::shared_ptr<Sensor>> result;

    for (const auto& [id, sensor] : sensors_)
    {
        if (sensor->getContext().type == type)
        {
            result.push_back(sensor);
        }
    }

    return result;
}

////////////////////////////////////////////////////////////

void SensorManager::clear()
{
    sensors_.clear();
}