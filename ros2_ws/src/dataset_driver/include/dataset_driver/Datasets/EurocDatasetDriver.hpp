//All datasets in Euroc have 2 cameras and 1 IMU
//Actual dataset will be specified in a YAML config file

#pragma once

#include<memory>
#include<string>
#include<vector>

#include<eigen3/Core>

#include"DatasetDriver.hpp"
#include"SensorManager.hpp"

class EurocDatasetDriver : public DatasetDriver{
public:
EurocDatasetDriver() = default;
    ~EurocDatasetDriver() override = default;

    bool initialize(const std::string& datasetPath,SensorManager& sensorManager) override;

    std::shared_ptr<RawSensorData> readNextMeasurement() override;

    void reset() override;

    bool finished() const override;

private:
    bool loadCamera0();
    bool loadCamera1();
    bool loadIMU();

    std::filesystem::path datasetPath_;

    // Sensor descriptions
    SensorContext cam0Context_;
    SensorContext cam1Context_;
    SensorContext imu0Context_;

    // Camera 0
    std::vector<std::string> cam0ImageFiles_;
    std::vector<double> cam0Timestamps_;
    size_t cam0Index_ = 0;

    // Camera 1
    std::vector<std::string> cam1ImageFiles_;
    std::vector<double> cam1Timestamps_;
    size_t cam1Index_ = 0;

    // IMU
    struct ImuMeasurement
    {
        double timestamp;

        Eigen::Vector3d acceleration;

        Eigen::Vector3d angularVelocity;
    };

    std::vector<ImuMeasurement> imuMeasurements_;
    size_t imuIndex_ = 0;
}