#include "distortPixels.hpp"

Eigen::Matrix3Xd distortPixels(const Eigen::Matrix3Xd& uv, const Eigen::Matrix3d& K, const Eigen::Vector2d& D)
{
    const Eigen::Vector2d center(K(0, 2), K(1, 2));   // principal point (u0, v0)
    const double k1 = D(0);
    const double k2 = D(1);

    Eigen::Matrix3Xd uvd = uv;   // copy keeps the row of 1s

    for (Eigen::Index i = 0; i < uv.cols(); ++i) {
        const Eigen::Vector2d offset = uv.col(i).head<2>() - center;   // (u - u0, v - v0)
        const double r2 = offset.squaredNorm();                        // r^2
        const double factor = 1.0 + k1 * r2 + k2 * r2 * r2;           // 1 + k1 r^2 + k2 r^4

        uvd.col(i).head<2>() = factor * offset + center;
    }

    return uvd;
}
