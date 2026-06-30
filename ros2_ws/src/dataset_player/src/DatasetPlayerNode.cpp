#include "dataset_player/DatasetPlayerNode.hpp"

using namespace std::chrono_literals;

namespace dataset_player
{

DatasetPlayerNode::DatasetPlayerNode()
: Node("dataset_player")
{
    loadParameters();

    initializeDriver();

    initializePublishers();

    const auto period =
        std::chrono::duration<double>(1.0 / playback_rate_);

    timer_ = create_wall_timer(
        std::chrono::duration_cast<std::chrono::milliseconds>(period),
        std::bind(&DatasetPlayerNode::timerCallback, this));

    RCLCPP_INFO(get_logger(), "Dataset Player started.");
}

void DatasetPlayerNode::loadParameters()
{
    declare_parameter("dataset_path", "");
    declare_parameter("config_file", "");
    declare_parameter("playback_rate", 30.0);

    get_parameter("dataset_path", dataset_path_);
    get_parameter("config_file", config_file_);
    get_parameter("playback_rate", playback_rate_);
}

void DatasetPlayerNode::initializeDriver()
{
    driver_ = std::make_shared<dataset_driver::DatasetDriver>();

    if (!driver_->initialize(dataset_path_, config_file_))
    {
        throw std::runtime_error("Failed to initialize Dataset Driver");
    }
}

void DatasetPlayerNode::initializePublishers()
{
    publisherManager_ =
        std::make_unique<PublisherManager>(shared_from_this());

    publisherManager_->initialize(driver_->getSensorManager());
}

void DatasetPlayerNode::timerCallback()
{
    auto bundle = driver_->next();

    if (!bundle)
    {
        RCLCPP_INFO(get_logger(), "Dataset finished.");

        timer_->cancel();

        return;
    }

    publisherManager_->publish(*bundle);
}

}