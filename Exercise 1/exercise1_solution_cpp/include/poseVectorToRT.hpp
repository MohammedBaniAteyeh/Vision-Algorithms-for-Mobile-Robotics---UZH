#pragma once

#include "dataTypes.hpp"

// A helper function that extracts [R|t] from an axis angle
RotTrans poseVectorToRT(const PoseVector& x);