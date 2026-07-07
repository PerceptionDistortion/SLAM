#pragma once

#include<memory>
#include<string>

#include<rclcpp/rclcpp.hpp>

#include"sensor_driver/SensorManager.hpp"
#include"sensor_driver/sensor_drivers/SensorDriver.hpp"
#include"dataset_player/publishers/PublisherManager.hpp"

//This will use Yaml config to create a sensor driver
//Will be agnostic against driver and init it
//Will init publishermanager
class DatasetPlayerNode : public rclcpp::Node{
public:
    DatasetPlayerNode();

private:
    void loadParameters();

    void initializeDriver();

    void initializePublishers();

    void timerCallback();

     // Parameters
    std::string datasetType_;
    std::string datasetPath_;
    double playbackRate_ = 30.0;

    // ROS
    rclcpp::TimerBase::SharedPtr timer_;

    // Sensor infrastructure
    SensorManager sensorManager_;

    // Driver abstraction
    std::shared_ptr<SensorDriver> driver_;

    // Publisher manager
    std::unique_ptr<PublisherManager> publisherManager_;
};