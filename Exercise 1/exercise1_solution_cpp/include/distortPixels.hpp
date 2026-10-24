#pragma once

#include <Eigen/Dense>

// Applies radial lens distortion (Gamma) to ideal pixel coordinates.
// uv: one point per column, rows (u, v, 1) as returned by projectPoints.
// K:  camera matrix, gives the principal point (u0, v0).
// D:  distortion coefficients (k1, k2) as returned by loadD.
// Returns the distorted pixels (ud, vd, 1), same layout as uv.
Eigen::Matrix3Xd distortPixels(const Eigen::Matrix3Xd& uv, const Eigen::Matrix3d& K, const Eigen::Vector2d& D);
