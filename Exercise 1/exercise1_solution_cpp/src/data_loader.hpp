#pragma once

#include <string>
#include <vector>

#include <Eigen/Dense>

// One camera pose: (wx, wy, wz, tx, ty, tz)
using PoseVector = Eigen::Matrix<double, 6, 1>;

// Camera matrix K (3x3) from K.txt
Eigen::Matrix3d loadK(const std::string& path);

// Distortion coefficients (k1, k2) from D.txt
Eigen::Vector2d loadD(const std::string& path);

// All camera poses from poses.txt, one per line
std::vector<PoseVector> loadPoses(const std::string& path);
