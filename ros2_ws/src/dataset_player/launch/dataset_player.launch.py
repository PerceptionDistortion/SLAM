from launch import LaunchDescription

from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():

    package_share = get_package_share_directory(
        "dataset_player"
    )

    config_file = os.path.join(
        package_share,
        "config",
        "euroc.yaml"
    )

    dataset_player = Node(
        package="dataset_player",
        executable="dataset_player_node",
        name="dataset_player",
        output="screen",
        emulate_tty=True,
        parameters=[config_file]
    )

    return LaunchDescription([
        dataset_player
    ])