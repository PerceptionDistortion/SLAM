#include <memory>

#include <rclcpp/rclcpp.hpp>

#include "dataset_player/DatasetPlayerNode.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<DatasetPlayerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}