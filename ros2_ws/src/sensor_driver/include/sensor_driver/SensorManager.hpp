#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "sensor_driver/sensors/Sensor.hpp"

class SensorManager
{
public:

    SensorManager() = default;
    ~SensorManager() = default;

    /// Register a sensor.
    bool registerSensor(const std::shared_ptr<Sensor>& sensor);

    /// Get a sensor by ID.
    std::shared_ptr<Sensor> getSensor(const std::string& sensorId) const;

    /// Get all registered sensors.
    std::vector<std::shared_ptr<Sensor>> getSensors() const;

    /// Check whether a sensor exists.
    bool hasSensor(const std::string& sensorId) const;

    /// Remove all registered sensors.
    void clear();

    /// Number of registered sensors.
    std::size_t size() const;

    /// Returns true if no sensors are registered.
    bool empty() const;

    /// Typed lookup.
    template<typename T>
    std::shared_ptr<T> getSensor(const std::string& sensorId) const;

private:

    std::unordered_map<std::string,std::shared_ptr<Sensor>> sensors_;
};