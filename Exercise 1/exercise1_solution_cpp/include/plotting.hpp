#pragma once

#include <string>
#include <utility>
#include <vector>

#include <Eigen/Dense>
#include <opencv2/core.hpp>

// Returns a 3-channel (BGR) copy of a grayscale image, so we can draw in color on it.
cv::Mat grayToColor(const cv::Mat& gray);

// Draws one dot per column of uv. Row 0 = u (column in the image), row 1 = v (row in the image).
// Extra rows (e.g. the homogeneous 1) are ignored, so both 2xN and 3xN work.
void drawPoints(cv::Mat& img, const Eigen::MatrixXd& uv,
                const cv::Scalar& color = cv::Scalar(0, 0, 255), int radius = 3);

// Draws one line per edge. Each edge is a pair of column indices (i, j) into uv:
// a line goes from point i to point j.
void drawEdges(cv::Mat& img, const Eigen::MatrixXd& uv, const std::vector<std::pair<int, int>>& edges,
               const cv::Scalar& color = cv::Scalar(0, 0, 255), int thickness = 2);

// Shows the image in a window and waits until a key is pressed.
void showImage(const std::string& title, const cv::Mat& img);
