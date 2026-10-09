#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "data_loader.hpp"


int main()
{
    const std::string data = DATA_DIR;
    Eigen::Matrix3d K = loadK(data + "/K.txt");
    std::vector<PoseVector> poses = loadPoses(data + "/poses.txt");

    PoseVector pose0 = poses[0];   // pose for img_0001.jpg

    std::cout << pose0;
    const std::string img_path = data + "/images/img_0001.jpg";
    
    return 0;
}
