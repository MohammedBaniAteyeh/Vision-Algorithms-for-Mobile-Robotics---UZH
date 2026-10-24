#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp> 

#include "dataLoader.hpp"
#include "projectPoints.hpp"
#include "poseVectorToRT.hpp"
#include "plotting.hpp"
#include "distortPixels.hpp"


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

// The 8 vertices of a cube standing on the board, as a 4x8 homogeneous matrix.
// (x0, y0) = world position of one bottom corner, side = edge length, all in metres.
// Columns 0-3: bottom face (Z = 0), columns 4-7: top face (Z = -side, since +Z points into the board).
// Both faces go around in the same order, so vertex i + 4 sits right above vertex i.
Eigen::Matrix4Xd makeCube(double x0, double y0, double side)
{
    const double x1 = x0 + side;
    const double y1 = y0 + side;
    const double z  = -side;

    Eigen::Matrix4Xd cube(4, 8);
    cube << x0, x1, x1, x0,   x0, x1, x1, x0,     // X
            y0, y0, y1, y1,   y0, y0, y1, y1,     // Y
            0,  0,  0,  0,    z,  z,  z,  z,      // Z
            1,  1,  1,  1,    1,  1,  1,  1;      // homogeneous 1
    return cube;
}

// The 12 cube edges as pairs of column indices into makeCube()'s matrix.
std::vector<std::pair<int, int>> cubeEdges()
{
    return {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},   // bottom face
        {4, 5}, {5, 6}, {6, 7}, {7, 4},   // top face
        {0, 4}, {1, 5}, {2, 6}, {3, 7},   // vertical edges
    };
}

int main()
{
    const std::string data = DATA_DIR;

    Eigen::Matrix3d K = loadK(data + "/K.txt");

    std::vector<PoseVector> poses = loadPoses(data + "/poses.txt");

    RotTrans T = poseVectorToRT(poses.at(0));

    // --- Part 1: corners and cube on the undistorted image ---
    Eigen::Matrix4Xd Pw = makeCheckerboardCorners(9, 6, 0.04);

    Eigen::Matrix3Xd pxls = projectPoints(K, T, Pw);

    const std::string img_path = data + "/images_undistorted/img_0001.jpg";

    cv::Mat img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);

    const double square = 0.04;
    Eigen::Matrix4Xd cube = makeCube(2 * square, 1 * square, 2 * square);
    Eigen::Matrix3Xd cube_pxls = projectPoints(K, T, cube);

    cv::Mat img_color = grayToColor(img);
    // drawPoints(img_color, pxls);
    drawEdges(img_color, cube_pxls, cubeEdges());
    showImage("projection", img_color);

    // --- Part 2: projection onto the raw (distorted) image ---
    Eigen::Vector2d D = loadD(data + "/D.txt");
    Eigen::Matrix3Xd pxls_distorted = distortPixels(pxls, K, D);

    cv::Mat raw = cv::imread(data + "/images/img_0001.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat raw_color = grayToColor(raw);
    drawPoints(raw_color, pxls, cv::Scalar(255, 0, 0));   // blue: ideal pixels (no distortion)
    drawPoints(raw_color, pxls_distorted);                 // red: distorted pixels
    showImage("distorted projection", raw_color);

    return 0;
}
