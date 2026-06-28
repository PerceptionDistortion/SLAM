#pragma once

#include <opencv2/core.hpp>

#include "RawSensorData.hpp"

class CameraRawData : public RawSensorData
{
public:
    CameraRawData() = default;

    CameraRawData(const SensorContext& context,double timestamp,const cv::Mat& image)
        : RawSensorData(context, timestamp),image(image){}

    cv::Mat image;
};
