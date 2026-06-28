//Abstract class
//Dataset specific dataset format

#pragma once

#include <memory>
#include <string>

#include "SensorManager.hpp"
#include "RawSensorData.hpp"

class DatasetDriver
{
public:
    virtual ~DatasetDriver() = default;

    /// Load dataset and register available sensors.
    virtual bool initialize(const std::string& datasetPath,SensorManager& sensorManager) = 0;

    /// Read the next available sensor measurement.
    /// Returns nullptr when the dataset has finished.
    virtual std::shared_ptr<RawSensorData> readNextMeasurement() = 0;

    /// Restart playback from the beginning.
    virtual void reset() = 0;

    /// True when no more measurements remain.
    virtual bool finished() const = 0;
};