#pragma once

#include<filesystem>

#include"sensor_drivers/SensorDriver.hpp"

class DatasetDriver: public SensorDriver{
public:
    explicit DatasetDriver(const std::filesystem::path& datasetPath)
        : datasetPath_(datasetPath){}
        
protected:
    std::filesystem::path datasetPath_;
};