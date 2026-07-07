#pragma once

#include "sensor_driver/raw_sensor_data/RawSensorData.hpp"
#include "sensor_driver/sensors/CameraSensor.hpp"

class CameraRawData : public RawSensorData
{
public:

    CameraRawData(
        std::shared_ptr<CameraSensor> sensor,double timestamp,const cv::Mat& image)
        :RawSensorData(sensor, timestamp),image(image){}

    cv::Mat image;
};