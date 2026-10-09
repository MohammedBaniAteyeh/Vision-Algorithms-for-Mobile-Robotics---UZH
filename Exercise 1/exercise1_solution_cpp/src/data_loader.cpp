#include "data_loader.hpp"

#include <fstream>
#include <stdexcept>

// Reads every number in a text file, in order, ignoring spaces and line breaks.
static std::vector<double> readNumbers(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open " + path);
    }

    std::vector<double> numbers;
    double value;
    while (file >> value) {
        numbers.push_back(value);
    }
    return numbers;
}

Eigen::Matrix3d loadK(const std::string& path)
{
    std::vector<double> n = readNumbers(path);
    if (n.size() != 9) {
        throw std::runtime_error(path + ": expected 9 numbers, got " + std::to_string(n.size()));
    }

    Eigen::Matrix3d K;
    K << n[0], n[1], n[2],
         n[3], n[4], n[5],
         n[6], n[7], n[8];
    return K;
}

Eigen::Vector2d loadD(const std::string& path)
{
    std::vector<double> n = readNumbers(path);
    if (n.size() != 2) {
        throw std::runtime_error(path + ": expected 2 numbers, got " + std::to_string(n.size()));
    }

    return Eigen::Vector2d(n[0], n[1]);
}

std::vector<PoseVector> loadPoses(const std::string& path)
{
    std::vector<double> n = readNumbers(path);
    if (n.size() % 6 != 0) {
        throw std::runtime_error(path + ": number count is not a multiple of 6");
    }

    std::vector<PoseVector> poses;
    for (std::size_t i = 0; i < n.size(); i += 6) {
        PoseVector p;
        p << n[i], n[i + 1], n[i + 2], n[i + 3], n[i + 4], n[i + 5];
        poses.push_back(p);
    }
    return poses;
}
