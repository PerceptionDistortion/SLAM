#include "dataset_player/DatasetPlayerNode.hpp"

#include <chrono>
#include <functional>
#include <stdexcept>

#include "sensor_driver/sensor_drivers/EurocDatasetDriver.hpp"

using namespace std::chrono_literals;

DatasetPlayerNode::DatasetPlayerNode()
    : rclcpp::Node("dataset_player")
{
    loadParameters();

    initializeDriver();

    initializePublishers();

    auto timerPeriod =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::duration<double>(1.0 / playbackRate_));

    timer_ = create_wall_timer(
        timerPeriod,
        std::bind(&DatasetPlayerNode::timerCallback, this));

    RCLCPP_INFO(get_logger(), "Dataset Player initialized.");
}

void DatasetPlayerNode::loadParameters()
{
    declare_parameter<std::string>(
        "dataset_type",
        "euroc");

    declare_parameter<std::string>(
        "dataset_path",
        "");

    declare_parameter<double>(
        "playback_rate",
        30.0);

    get_parameter("dataset_type", datasetType_);
    get_parameter("dataset_path", datasetPath_);
    get_parameter("playback_rate", playbackRate_);
}

void DatasetPlayerNode::initializeDriver()
{
    if (datasetType_ == "euroc")
    {
        driver_ =
            std::make_shared<EurocDatasetDriver>(datasetPath_);
    }
    else
    {
        throw std::runtime_error(
            "Unsupported dataset type: " + datasetType_);
    }

    if (!driver_->init(sensorManager_))
    {
        throw std::runtime_error(
            "Failed to initialize dataset driver.");
    }

    RCLCPP_INFO(
        get_logger(),
        "Dataset driver initialized.");
}

void DatasetPlayerNode::initializePublishers()
{
    publisherManager_ =
        std::make_unique<PublisherManager>(
            shared_from_this());

    publisherManager_->initialize(sensorManager_);

    RCLCPP_INFO(
        get_logger(),
        "Publishers initialized.");
}

void DatasetPlayerNode::timerCallback()
{
    if (driver_->finished())
    {
        RCLCPP_INFO(
            get_logger(),
            "Dataset playback completed.");

        timer_->cancel();
        return;
    }

    std::unique_ptr<SensorDataBundle> bundle =
        driver_->readNextBundle();

    if (!bundle)
    {
        return;
    }

    publisherManager_->publish(*bundle);
}