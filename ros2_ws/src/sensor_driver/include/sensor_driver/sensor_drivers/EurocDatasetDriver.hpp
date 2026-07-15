#pragma once

#include<vector>

#include<Eigen/Dense>
#include <fstream>
#include <sstream>
#include <limits>

#include "sensor_driver/sensor_drivers/DatasetDriver.hpp"
#include "sensor_driver/sensors/CameraSensor.hpp"
#include "sensor_driver/sensors/ImuSensor.hpp"
#include"sensor_driver/calibration/EurocCalibration.hpp"
#include "sensor_driver/SensorDataBundle.hpp"
#include "sensor_driver/raw_sensor_data/CameraRawData.hpp"
#include "sensor_driver/raw_sensor_data/ImuRawData.hpp"

//Sensors will be owned by concrete drivers instead of abstractions
class EurocDatasetDriver:public DatasetDriver{
public:
    explicit EurocDatasetDriver(const std::filesystem::path& datasetPath);

    //Overriden methods
    
    //Sensor Driver
    //Gets the next data available from any sensor
    //From here the raw sensor data is originated
    //Reads individual sensor data and creates a bundle
    //Chronologically fetches data from dataset
    virtual std::unique_ptr<SensorDataBundle> readNextBundle() override;

    //create the sensors
    virtual bool init(SensorManager& sensorManager) override;

    virtual void reset() override;

    virtual bool finished() const override;

private:
    //Sensor manager sets them as active sensors
    //These can be used as desired by respective SLAM systems
    bool registerSensors(SensorManager& sensorManager);

    static double toSeconds(uint64_t timestamp);

    //CAMERA DATA and INTERNAL DATASET DATA STRUCTURES
    struct CameraFrame{
        uint64_t timestamp = 0;
        std::filesystem::path imagePath;
    };
    std::vector<CameraFrame> cam0Frames_;
    std::vector<CameraFrame> cam1Frames_;

    bool loadCamera(
        const std::string& sensorName,
        std::vector<CameraFrame>& frames,
        std::shared_ptr<CameraSensor>& sensor);

    //IMU DATA and INTERNAL DATA STRUCTURES
    struct ImuMeasurement
    {
        uint64_t timestamp = 0;
        Eigen::Vector3d acceleration =Eigen::Vector3d::Zero();
        Eigen::Vector3d angularVelocity =Eigen::Vector3d::Zero();
    };
    std::vector<ImuMeasurement> imuMeasurements_;

    bool loadImu(
        std::vector<ImuMeasurement>& measurements,
        std::shared_ptr<ImuSensor>& sensor);


    //PLAYBACK INDICES
    std::size_t cam0Index_ = 0;
    std::size_t cam1Index_ = 0;
    std::size_t imuIndex_ = 0;

    //SENSORS
    //Holds sensor contexts
    std::shared_ptr<CameraSensor> cam0_;
    std::shared_ptr<CameraSensor> cam1_;
    std::shared_ptr<ImuSensor> imu_;
};