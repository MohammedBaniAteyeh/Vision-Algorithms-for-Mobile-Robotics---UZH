#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "dataTypes.hpp"

Eigen::Matrix3Xd projectPoints(const Eigen::Matrix3d& K, const RotTrans& T, const Eigen::Matrix4Xd& Pw);
