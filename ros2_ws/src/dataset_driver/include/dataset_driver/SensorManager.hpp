//Registry system for sensors

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "dataset_driver/sensor_definition/Sensor.hpp"
#include "dataset_driver/SensorType.hpp"

class SensorManager
{
public:
    SensorManager() = default;
    ~SensorManager() = default;

    /// Register a new sensor.
    bool addSensor(const std::shared_ptr<Sensor>& sensor);

    /// Remove a sensor by its ID.
    bool removeSensor(const std::string& sensorId);

    /// Check whether a sensor exists.
    bool hasSensor(const std::string& sensorId) const;

    /// Get a sensor by its ID.
    std::shared_ptr<Sensor> getSensor(const std::string& sensorId) const;

    /// Get all registered sensors.
    std::vector<std::shared_ptr<Sensor>> getSensors() const;

    /// Get all sensors of a given type.
    std::vector<std::shared_ptr<Sensor>> getSensors(SensorType type) const;

    /// Remove all sensors.
    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Sensor>> sensors_;
};