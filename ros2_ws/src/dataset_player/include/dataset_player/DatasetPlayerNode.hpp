//Init the dataset driver
//Create ROS publisher for the dataset
//Read raw sensor data
//Convert data to ROS messages
//Publish topics
#pragma once

#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "PublisherManager.hpp"

#include "dataset_driver/DatasetDriver.hpp"

namespace dataset_player
{

class DatasetPlayerNode : public rclcpp::Node
{
public:
    DatasetPlayerNode();

private:
    void loadParameters();
    void initializeDriver();
    void initializePublishers();

    void timerCallback();

private:
    std::string dataset_path_;
    std::string config_file_;

    double playback_rate_;

    rclcpp::TimerBase::SharedPtr timer_;

    std::shared_ptr<dataset_driver::DatasetDriver> driver_;

    std::unique_ptr<PublisherManager> publisherManager_;
};

}