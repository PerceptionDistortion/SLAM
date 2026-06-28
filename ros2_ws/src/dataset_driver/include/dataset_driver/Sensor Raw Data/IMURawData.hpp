#pragma once

#include <Eigen/Dense>

#include "RawSensorData.hpp"

class ImuRawData : public RawSensorData
{
public:
    ImuRawData() = default;

    ImuRawData(const SensorContext& context,
               double timestamp,
               const Eigen::Vector3d& acceleration,
               const Eigen::Vector3d& angularVelocity)
        : RawSensorData(context, timestamp),acceleration(acceleration),angularVelocity(angularVelocity){}

    Eigen::Vector3d acceleration = Eigen::Vector3d::Zero();
    Eigen::Vector3d angularVelocity = Eigen::Vector3d::Zero();
};
