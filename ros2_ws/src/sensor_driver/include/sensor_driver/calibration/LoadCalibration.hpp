#pragma once

#include "sensor_driver/calibration/Calibration.hpp"

class LoadCalibration : public Calibration
{
public:

    explicit LoadCalibration(const std::filesystem::path& source): source_(source){}

protected:

    std::filesystem::path source_;
};