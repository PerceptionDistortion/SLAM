#pragma once

#include <deque>
#include <memory>
#include <mutex>

#include "dataset_driver/sensor_raw_data/RawSensorData.hpp"

class SensorBuffer
{
public:
    SensorBuffer() = default;
    virtual ~SensorBuffer() = default;

    void push(const std::shared_ptr<RawSensorData>& data)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_.push_back(data);
    }

    bool pop(std::shared_ptr<RawSensorData>& data)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (buffer_.empty())
            return false;

        data = buffer_.front();
        buffer_.pop_front();

        return true;
    }

    bool popLatest(std::shared_ptr<RawSensorData>& data)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (buffer_.empty())
            return false;

        data = buffer_.back();
        buffer_.clear();

        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return buffer_.empty();
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return buffer_.size();
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_.clear();
    }

protected:
    std::deque<std::shared_ptr<RawSensorData>> buffer_;

    mutable std::mutex mutex_;
};