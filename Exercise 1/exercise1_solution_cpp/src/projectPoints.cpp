#include "projectPoints.hpp"

// in pixels = K * [R | t] Pw = [X Y Z] = [X/Z Y/Z 1]


Eigen::Matrix3Xd projectPoints(const Eigen::Matrix3d& K, const RotTrans& T, const Eigen::Matrix4Xd& Pw){
    
    Eigen::Matrix3Xd Pxl = K * T * Pw;

    int cols = Pxl.cols();

    for(int i = 0; i < cols; i++){

        Pxl(0,i) = Pxl(0,i) / Pxl(2,i);
        Pxl(1,i) = Pxl(1,i) / Pxl(2,i); 
        Pxl(2,i) = 1;

    }

    return Pxl;

};