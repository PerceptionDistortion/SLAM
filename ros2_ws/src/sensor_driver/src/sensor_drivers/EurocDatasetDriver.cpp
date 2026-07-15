#include "sensor_driver/sensor_drivers/EurocDatasetDriver.hpp"

#include<opencv2/opencv.hpp>

#include"sensor_driver/SensorManager.hpp"

//CONSTRUCTOR
EurocDatasetDriver::EurocDatasetDriver(
    const std::filesystem::path& datasetPath)
    : DatasetDriver(datasetPath){}

double EurocDatasetDriver::toSeconds(uint64_t timestamp)
{
    return static_cast<double>(timestamp) * 1e-9;
}

bool EurocDatasetDriver::init(SensorManager& sensorManager)
{
    cam0Frames_.clear();
    cam1Frames_.clear();
    imuMeasurements_.clear();

    cam0Index_ = 0;
    cam1Index_ = 0;
    imuIndex_ = 0;

    //LOAD DATASET
    if (!loadCamera("cam0", cam0Frames_, cam0_)) return false;
    if (!loadCamera("cam1", cam1Frames_, cam1_))  return false;
    if (!loadImu(imuMeasurements_, imu_)) return false;

    //REGISTER SENSORS
    return registerSensors(sensorManager);
}

bool EurocDatasetDriver::registerSensors(SensorManager& sensorManager)
{
    if (!cam0_ || !cam1_ || !imu_) return false;
    if (!sensorManager.registerSensor(cam0_)) return false;
    if (!sensorManager.registerSensor(cam1_)) return false;
    if (!sensorManager.registerSensor(imu_)) return false;
    return true;
}

bool EurocDatasetDriver::loadCamera(
    const std::string& sensorName,
    std::vector<CameraFrame>& frames,
    std::shared_ptr<CameraSensor>& sensor)
{
    frames.clear();

    //--------------------------------------------------------
    // Dataset Paths
    //--------------------------------------------------------

    const auto cameraFolder = datasetPath_ / "mav0" / sensorName;

    const auto csvFile = cameraFolder / "data.csv";

    const auto calibrationFile = cameraFolder / "sensor.yaml";

    const auto imageFolder = cameraFolder / "data";

    //--------------------------------------------------------
    // Create Sensor
    //--------------------------------------------------------

    SensorContext context;

    context.id = sensorName;
    context.type = SensorType::camera;
    context.frameID = sensorName;
    context.frequency = 20.0;          // EuRoC cameras

    sensor = std::make_shared<CameraSensor>(context);

    //--------------------------------------------------------
    // Load Calibration
    //--------------------------------------------------------

    EurocCalibration calibration(calibrationFile);

    if (!calibration.calibrate(*sensor))
    {
        return false;
    }

    //--------------------------------------------------------
    // Read CSV
    //--------------------------------------------------------

    std::ifstream file(csvFile);

    if (!file.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        if (line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string timestampString;
        std::string filename;

        if (!std::getline(ss, timestampString, ','))
            continue;

        if (!std::getline(ss, filename))
            continue;

        CameraFrame frame;

        frame.timestamp = std::stoull(timestampString);

        frame.imagePath = imageFolder / filename;

        frames.emplace_back(std::move(frame));
    }

    return true;
}

bool EurocDatasetDriver::loadImu(
    std::vector<ImuMeasurement>& measurements,
    std::shared_ptr<ImuSensor>& sensor)
{
    measurements.clear();

    //--------------------------------------------------------
    // Dataset Paths
    //--------------------------------------------------------

    const auto imuFolder = datasetPath_ / "mav0" / "imu0";

    const auto csvFile = imuFolder / "data.csv";

    const auto calibrationFile = imuFolder / "sensor.yaml";

    //--------------------------------------------------------
    // Create Sensor
    //--------------------------------------------------------

    SensorContext context;

    context.id = "imu0";
    context.type = SensorType::imu;
    context.frameID = "imu0";
    context.frequency = 200.0;      // EuRoC IMU

    sensor = std::make_shared<ImuSensor>(context);

    //--------------------------------------------------------
    // Load Calibration
    //--------------------------------------------------------

    EurocCalibration calibration(calibrationFile);

    if (!calibration.calibrate(*sensor))
    {
        return false;
    }

    //--------------------------------------------------------
    // Open CSV
    //--------------------------------------------------------

    std::ifstream file(csvFile);

    if (!file.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        if (line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string token;

        ImuMeasurement measurement;

        //----------------------------------------------------
        // Timestamp
        //----------------------------------------------------

        if (!std::getline(ss, token, ','))
            continue;

        measurement.timestamp = std::stoull(token);

        //----------------------------------------------------
        // Angular velocity
        //----------------------------------------------------

        for (int i = 0; i < 3; ++i)
        {
            if (!std::getline(ss, token, ','))
                return false;

            measurement.angularVelocity(i) =
                std::stod(token);
        }

        //----------------------------------------------------
        // Linear acceleration
        //----------------------------------------------------

        for (int i = 0; i < 3; ++i)
        {
            if (!std::getline(ss, token, ','))
                return false;

            measurement.acceleration(i) =
                std::stod(token);
        }

        measurements.emplace_back(std::move(measurement));
    }

    return true;
}

bool EurocDatasetDriver::finished() const
{
    return cam0Index_ >= cam0Frames_.size() &&
           cam1Index_ >= cam1Frames_.size() &&
           imuIndex_ >= imuMeasurements_.size();
}

void EurocDatasetDriver::reset()
{
    cam0Index_ = 0;
    cam1Index_ = 0;
    imuIndex_ = 0;
}

std::unique_ptr<SensorDataBundle> EurocDatasetDriver::readNextBundle()
{
    if (finished())
    {
        return nullptr;
    }

    auto bundle = std::make_unique<SensorDataBundle>();

    //--------------------------------------------------------
    // Find earliest timestamp among all sensors
    //--------------------------------------------------------

    uint64_t nextTimestamp = std::numeric_limits<uint64_t>::max();

    if (cam0Index_ < cam0Frames_.size())
    {
        nextTimestamp =
            std::min(nextTimestamp,
                     cam0Frames_[cam0Index_].timestamp);
    }

    if (cam1Index_ < cam1Frames_.size())
    {
        nextTimestamp =
            std::min(nextTimestamp,
                     cam1Frames_[cam1Index_].timestamp);
    }

    if (imuIndex_ < imuMeasurements_.size())
    {
        nextTimestamp =
            std::min(nextTimestamp,
                     imuMeasurements_[imuIndex_].timestamp);
    }

    //--------------------------------------------------------
    // Camera 0
    //--------------------------------------------------------

    if (cam0Index_ < cam0Frames_.size() &&
        cam0Frames_[cam0Index_].timestamp == nextTimestamp)
    {
        cv::Mat image =
            cv::imread(
                cam0Frames_[cam0Index_].imagePath.string(),
                cv::IMREAD_GRAYSCALE);

        if (!image.empty())
        {
            bundle->addData(
                std::make_shared<CameraRawData>(
                    cam0_,
                    toSeconds(nextTimestamp),
                    image));
        }

        ++cam0Index_;
    }

    //--------------------------------------------------------
    // Camera 1
    //--------------------------------------------------------

    if (cam1Index_ < cam1Frames_.size() &&
        cam1Frames_[cam1Index_].timestamp == nextTimestamp)
    {
        cv::Mat image =
            cv::imread(
                cam1Frames_[cam1Index_].imagePath.string(),
                cv::IMREAD_GRAYSCALE);

        if (!image.empty())
        {
            bundle->addData(
                std::make_shared<CameraRawData>(
                    cam1_,
                    toSeconds(nextTimestamp),
                    image));
        }

        ++cam1Index_;
    }

    //--------------------------------------------------------
    // IMU
    //--------------------------------------------------------

    while (imuIndex_ < imuMeasurements_.size() &&
           imuMeasurements_[imuIndex_].timestamp == nextTimestamp)
    {
        const auto& imu = imuMeasurements_[imuIndex_];

        bundle->addData(
            std::make_shared<ImuRawData>(
                imu_,
                toSeconds(imu.timestamp),
                imu.acceleration,
                imu.angularVelocity));

        ++imuIndex_;
    }

    return bundle;
}
