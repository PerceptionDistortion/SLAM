#pragma once

#include <memory>

#include "sensors/SensorContext.hpp"

class Sensor
{
public:

    explicit Sensor(const SensorContext& context): context_(context){}

    virtual ~Sensor() = default;

    const SensorContext& context() const
    {
        return context_;
    }

    const std::string& id() const
    {
        return context_.id;
    }

    SensorType type() const
    {
        return context_.type;
    }

    const std::string& frameId() const
    {
        return context_.frameID;
    }

    double frequency() const
    {
        return context_.frequency;
    }

protected:

    SensorContext context_;
};