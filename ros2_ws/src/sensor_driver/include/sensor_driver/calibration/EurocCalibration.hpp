#pragma once

#include "sensor_driver/calibration/LoadCalibration.hpp"

class EurocCalibration : public LoadCalibration
{
public:
    explicit EurocCalibration(const std::filesystem::path& sensorYaml);
    bool calibrate(CameraSensor& sensor) override;
    bool calibrate(ImuSensor& sensor) override;
};