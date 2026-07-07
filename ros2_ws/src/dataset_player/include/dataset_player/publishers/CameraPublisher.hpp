#include"SensorPublisher.hpp"

class CameraPublisher : public SensorPublisher
{
public:

    CameraPublisher(
        const rclcpp::Node::SharedPtr& node,
        std::shared_ptr<Sensor> sensor);

    void publish(
        const std::shared_ptr<RawSensorData>& data) override;

private:

    image_transport::Publisher imagePublisher_;
};