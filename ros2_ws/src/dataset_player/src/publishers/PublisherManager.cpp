#include "dataset_player/publishers/PublisherManager.hpp"

#include <stdexcept>

#include "dataset_player/publishers/CameraPublisher.hpp"
#include "dataset_player/publishers/ImuPublisher.hpp"

PublisherManager::PublisherManager(
    const rclcpp::Node::SharedPtr& node)
    : node_(node)
{
}

void PublisherManager::initialize(
    const SensorManager& sensorManager)
{
    publishers_.clear();

    for (const auto& sensor : sensorManager.getSensors())
    {
        switch (sensor->type())
        {
        case SensorType::camera:

            publishers_.emplace(
                sensor->id(),
                std::make_unique<CameraPublisher>(
                    node_,
                    sensor));

            break;

        case SensorType::imu:

            publishers_.emplace(
                sensor->id(),
                std::make_unique<ImuPublisher>(
                    node_,
                    sensor));

            break;

        default:
            break;
        }
    }
}

void PublisherManager::publish(
    const SensorDataBundle& bundle)
{
    for (const auto& data : bundle.getData())
    {
        auto sensor = data->sensor();

        auto it = publishers_.find(sensor->id());

        if (it == publishers_.end())
        {
            continue;
        }

        it->second->publish(data);
    }
}