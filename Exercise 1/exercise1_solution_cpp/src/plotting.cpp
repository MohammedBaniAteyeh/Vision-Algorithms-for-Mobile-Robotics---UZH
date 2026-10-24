#include "plotting.hpp"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat grayToColor(const cv::Mat& gray)
{
    cv::Mat color;
    cv::cvtColor(gray, color, cv::COLOR_GRAY2BGR);
    return color;
}

void drawPoints(cv::Mat& img, const Eigen::MatrixXd& uv, const cv::Scalar& color, int radius)
{
    for (int i = 0; i < uv.cols(); ++i) {
        const cv::Point px(cvRound(uv(0, i)), cvRound(uv(1, i)));
        cv::circle(img, px, radius, color, cv::FILLED);
    }
}

void showImage(const std::string& title, const cv::Mat& img)
{
    cv::imshow(title, img);
    cv::waitKey(0);
}
