#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "data_loader.hpp"

// World positions of the checkerboard's inner corners as a 4xN homogeneous matrix:
// one corner per column (X, Y, Z, 1), filled row by row (all X for y = 0, then y = 1, ...).
Eigen::Matrix4Xd makeCheckerboardCorners(int nx, int ny, double square_size)
{
    Eigen::Matrix4Xd Pw(4, nx * ny);

    int col = 0;
    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            Pw.col(col) << x * square_size, y * square_size, 0.0, 1.0;
            ++col;
        }
    }
    return Pw;
}

int main()
{
    const std::string data = DATA_DIR;

    Eigen::Matrix3d K = loadK(data + "/K.txt");

    std::vector<PoseVector> poses = loadPoses(data + "/poses.txt");

    Eigen::Matrix4Xd Pw = makeCheckerboardCorners(9, 6, 0.04);

    const std::string img_path = data + "/images_undistorted/img_0001.jpg";

    cv::Mat img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);

    cv::imshow("test", img);

    cv::waitKey(0);

    return 0;
}
