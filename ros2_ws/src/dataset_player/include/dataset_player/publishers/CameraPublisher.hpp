#include"SensorPublisher.hpp"

class CameraPublisher : public SensorPublisher
{
public:

    CameraPublisher(rclcpp::Node* node,std::shared_ptr<Sensor> sensor);

    void publish(
        const std::shared_ptr<RawSensorData>& data) override;

private:

    image_transport::Publisher imagePublisher_;
};