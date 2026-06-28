//Represents a physical sensor that produces data

#pragma once

#include"SensorContext.hpp"

class Sensor
{
public:
    virtual ~Sensor() = default;

    explicit Sensor(const SensorContext& context);

    const SensorContext& getContext() const;

protected:
    SensorContext context_;
};