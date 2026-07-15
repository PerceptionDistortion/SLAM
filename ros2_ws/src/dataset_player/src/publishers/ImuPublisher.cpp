#include "dataset_player/publishers/ImuPublisher.hpp"
#include "sensor_driver/raw_sensor_data/ImuRawData.hpp"

ImuPublisher::ImuPublisher(
    rclcpp::Node* node,
    std::shared_ptr<Sensor> sensor)
    : SensorPublisher(node, std::move(sensor))
{
    imuPublisher_ =node_->create_publisher<sensor_msgs::msg::Imu>(
            sensor_->id() + "/imu",10);
}

void ImuPublisher::publish(const std::shared_ptr<RawSensorData>& data)
{
    auto imuData =std::dynamic_pointer_cast<ImuRawData>(data);
    if (!imuData) return;

    sensor_msgs::msg::Imu message;

    message.header.stamp =node_->get_clock()->now();

    message.header.frame_id =sensor_->frameId();

    message.linear_acceleration.x =
        imuData->acceleration.x();

    message.linear_acceleration.y =
        imuData->acceleration.y();

    message.linear_acceleration.z =
        imuData->acceleration.z();

    message.angular_velocity.x =
        imuData->angularVelocity.x();

    message.angular_velocity.y =
        imuData->angularVelocity.y();

    message.angular_velocity.z =
        imuData->angularVelocity.z();

    imuPublisher_->publish(message);
}