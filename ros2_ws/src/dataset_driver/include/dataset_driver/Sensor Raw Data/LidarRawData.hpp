#pragma once

#include <vector>

#include <Eigen/Core>

#include "RawSensorData.hpp"

class LidarRawData : public RawSensorData
{
public:
    LidarRawData() = default;

    LidarRawData(const SensorContext& context,double timestamp,
        const std::vector<Eigen::Vector3f>& points)
        : RawSensorData(context, timestamp),points(points){}

    std::vector<Eigen::Vector3f> points;
};
