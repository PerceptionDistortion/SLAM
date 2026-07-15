#include"sensor_driver/calibration/EurocCalibration.hpp"

#include<yaml-cpp/yaml.h>
#include <fstream>
#include <sstream>


#include"sensor_driver/sensors/CameraSensor.hpp"
#include"sensor_driver/sensors/ImuSensor.hpp"
#include"sensor_driver/calibration/EurocCalibration.hpp" //Calibration

EurocCalibration::EurocCalibration(
    const std::filesystem::path& sensorYaml): LoadCalibration(sensorYaml){}

bool EurocCalibration::calibrate(CameraSensor& sensor)
{
    YAML::Node yaml =YAML::LoadFile(source_.string());
    auto resolution =yaml["resolution"];
    sensor.width =resolution[0].as<int>();
    sensor.height =resolution[1].as<int>();
    auto intrinsics =yaml["intrinsics"];

    double fx = intrinsics[0].as<double>();
    double fy = intrinsics[1].as<double>(); 
    double cx = intrinsics[2].as<double>();
    double cy = intrinsics[3].as<double>();

    sensor.K =
        (cv::Mat_<double>(3,3)
            << fx,0,cx,
               0,fy,cy,
               0,0,1);

    auto dist =yaml["distortion_coefficients"];

    sensor.D =
        (cv::Mat_<double>(1,4)
            << dist[0].as<double>(),
               dist[1].as<double>(),
               dist[2].as<double>(),
               dist[3].as<double>());

    return true;
}

bool EurocCalibration::calibrate(
    ImuSensor& sensor)
{
    YAML::Node yaml =YAML::LoadFile(source_.string());
    sensor.gyroNoise =yaml["gyroscope_noise_density"].as<double>();
    sensor.accelNoise =yaml["accelerometer_noise_density"].as<double>();

    return true;
}

