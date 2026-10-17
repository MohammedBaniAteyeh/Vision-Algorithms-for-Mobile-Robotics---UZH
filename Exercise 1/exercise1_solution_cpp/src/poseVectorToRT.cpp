#include "poseVectorToRT.hpp"

RotTrans poseVectorToRT(const PoseVector& x){

    RotTrans RT;

    Eigen::Vector3d angle_v = x.head<3>();
    const double angle = angle_v.norm();

    Eigen::Vector3d t = x.tail<3>();

    Eigen::Matrix3d R = Eigen::AngleAxisd(angle, angle_v.normalized()).toRotationMatrix();

    RT.leftCols<3>() = R;
    RT.col(3)        = t;   

    return RT; 
};