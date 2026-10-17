#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>


// One camera pose: (wx, wy, wz, tx, ty, tz)
using PoseVector = Eigen::Matrix<double, 6, 1>;

// Camera Transforamtion Matrix [R|t]
using RotTrans = Eigen::Matrix<double, 3, 4>;