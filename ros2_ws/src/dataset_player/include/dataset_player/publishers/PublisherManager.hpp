#pragma once

#include <memory>
#include <unordered_map>

#include <rclcpp/rclcpp.hpp>

#include "sensor_driver/SensorManager.hpp"
#include "sensor_driver/SensorDataBundle.hpp"

#include "dataset_player/publishers/SensorPublisher.hpp"

class PublisherManager
{
public:

    explicit PublisherManager(rclcpp::Node* node);
    ~PublisherManager() = default;

    /// Create publishers for every registered sensor.
    void initialize(const SensorManager& sensorManager);

    /// Publish one chronological bundle.
    void publish(const SensorDataBundle& bundle);

private:

    rclcpp::Node* node_;
    std::unordered_map<std::string,std::unique_ptr<SensorPublisher>> publishers_;
};