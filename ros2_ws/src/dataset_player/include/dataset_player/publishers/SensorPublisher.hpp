#pragma once

#include<memory>
#include<string>

#include<rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>

#include "sensor_driver/sensors/Sensor.hpp"
#include "sensor_driver/raw_sensor_data/RawSensorData.hpp"

//Separates ROS publishing repsonsibilities
class SensorPublisher{
    public:
    SensorPublisher(
        const rclcpp::Node::SharedPtr& node,
        std::shared_ptr<Sensor> sensor)
        : node_(node),
          sensor_(std::move(sensor))
    {
    }

    virtual ~SensorPublisher() = default;

    /// Publish one piece of sensor data.
    virtual void publish(
        const std::shared_ptr<RawSensorData>& data) = 0;
    private:
    rclcpp::Node::SharedPtr node_;

    std::shared_ptr<Sensor> sensor_;
};