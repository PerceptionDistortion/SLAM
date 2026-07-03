#pragma once

#include<memory>

#include"sensor_driver/SensorManager.hpp"
#include"sensor_driver/SensorDataBundle.hpp"

//All drivers will originate from this
//Dataset based drivers
//Physical sensor drivers
//All sensor drivers will produce sensor data bundle on node request
class SensorDriver{
public:
    //default destructor for polymorphism
    virtual ~SensorDriver()=default;

    //register sensors with sensor manager
    virtual bool init(SensorManager& sensorManager)=0;

    //return next sensor bundle synced
    virtual std::unique_ptr<SensorDataBundle> readNextBundle()=0;

    //restart the driver
    virtual void reset()=0;

    //return true when no more data available
    virtual bool finished() const=0;
private:
};