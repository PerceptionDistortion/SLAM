#include"SensorPublisher.hpp"
#include <sensor_msgs/msg/imu.hpp>

class ImuPublisher : public SensorPublisher
{
public:

    ImuPublisher(
        const rclcpp::Node::SharedPtr& node,
        std::shared_ptr<Sensor> sensor);

    void publish(
        const std::shared_ptr<RawSensorData>& data) override;

private:

    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imuPublisher_;
};