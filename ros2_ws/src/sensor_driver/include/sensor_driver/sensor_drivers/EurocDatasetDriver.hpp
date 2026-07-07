#pragma once

#include<vector>

#include "sensor_driver/sensor_drivers/DatasetDriver.hpp"

//Forward declerations
class CameraRawData;
class ImuRawData;

//Sensors will be owned by concrete drivers instead of abstractions
class EurocDatasetDriver:public DatasetDriver{
public:
    explicit EurocDatasetDriver(const std::filesystem::path& datasetPath);

    //Overriden methods
    
    //Sensor Driver
    //Gets the next data when requested by the dataset node
    //From here the raw sensor data is originated
    //Reads individual sensor data and creates a bundle
    //Chronologically fetches data from dataset
    virtual std::unique_ptr<SensorDataBundle> readNextBundle() override;

    //create the sensors
    virtual bool init(SensorManager& sensorManager) override;

    virtual void reset() override;

    virtual bool finished() const override;

private:
    //Functions
     bool loadCamera(
        const std::string& sensorName,
        std::vector<std::string>& imageFiles,
        std::vector<uint64_t>& timestamps);

    bool loadImu();

    //Sensor mamager sets them as active sensors
    //These can be used as desired by respective SLAM systems
    bool registerSensors(
        SensorManager& sensorManager);
};