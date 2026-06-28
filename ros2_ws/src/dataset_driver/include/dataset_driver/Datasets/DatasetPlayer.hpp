//parser to use data from driver to sensor manager

#pragma once

#include <memory>

#include "DatasetDriver.hpp"
#include "SensorManager.hpp"

class DatasetPlayer
{
public:
    DatasetPlayer(std::shared_ptr<DatasetDriver> driver,
        std::shared_ptr<SensorManager> sensorManager);

    virtual ~DatasetPlayer() = default;

    /// Initialize the dataset.
    bool initialize(const std::string& datasetPath);

    /// Read and dispatch one measurement.
    bool update();

    /// Restart playback.
    void reset();

    /// Check whether playback has finished.
    bool finished() const;

private:
    std::shared_ptr<DatasetDriver> driver_;

    std::shared_ptr<SensorManager> sensorManager_;
};