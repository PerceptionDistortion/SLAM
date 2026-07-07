#pragma once

#include <Eigen/Dense>

#include "sensor_driver/raw_sensor_data/RawSensorData.hpp"

class ImuRawData : public RawSensorData
{
public:

    ImuRawData(
        std::shared_ptr<Sensor> sensor,double timestamp,
        const Eigen::Vector3d& acceleration,const Eigen::Vector3d& angularVelocity)
        : RawSensorData(sensor, timestamp),acceleration(acceleration),
          angularVelocity(angularVelocity){}

    Eigen::Vector3d acceleration;

    Eigen::Vector3d angularVelocity;
};