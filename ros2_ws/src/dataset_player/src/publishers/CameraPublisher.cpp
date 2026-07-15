#include "dataset_player/publishers/CameraPublisher.hpp"

#include <cv_bridge/cv_bridge.hpp>
#include <sensor_msgs/image_encodings.hpp>

#include "sensor_driver/raw_sensor_data/CameraRawData.hpp"

CameraPublisher::CameraPublisher(
    rclcpp::Node* node,
    std::shared_ptr<Sensor> sensor)
    : SensorPublisher(node, std::move(sensor))
{
    imagePublisher_ =
        image_transport::create_publisher(
            node_,
            sensor_->id() + "/image_raw");
}

void CameraPublisher::publish(
    const std::shared_ptr<RawSensorData>& data)
{
    auto cameraData =
        std::dynamic_pointer_cast<CameraRawData>(data);

    if (!cameraData)
    {
        return;
    }

    auto message =
        cv_bridge::CvImage(
            std_msgs::msg::Header(),
            sensor_msgs::image_encodings::MONO8,
            cameraData->image)
            .toImageMsg();

    message->header.stamp =
        node_->get_clock()->now();

    message->header.frame_id =
        sensor_->frameId();

    imagePublisher_.publish(message);
}