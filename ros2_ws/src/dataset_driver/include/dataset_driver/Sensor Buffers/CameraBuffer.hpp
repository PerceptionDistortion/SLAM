#pragma once

#include "SensorBuffer.hpp"
#include "CameraRawData.hpp"

class CameraBuffer : public SensorBuffer<CameraRawData>
{
};