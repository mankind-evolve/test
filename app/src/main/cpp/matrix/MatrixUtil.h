//
// Created by Admin on 2019/7/13.
//

#ifndef OPENGLES_STU_MATRIXUTIL_H
#define OPENGLES_STU_MATRIXUTIL_H


#include <math.h>

//初始化单位矩阵
//1,0,0,0,
//0,1,0,0,
//0,0,1,0,
//0,0,0,1,
static void initMatrix(float *matrix) {
    for (int i = 0; i < 16; i++) {
        if (i % 5 == 0) {
            matrix[i] = 1;
        } else {
            matrix[i] = 0;
        }
    }
}

//沿着z轴旋转
static void rotateMatrix_z(double angle, float *matrix) {
    angle = angle * (M_PI / 180.0);
    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);
}


//缩放公式
static void scaleMatrix(double scale, float* matrix){
    matrix[0] = scale;
    matrix[5] = scale;
}


//位移公式
static void tranMatrix(double x, double y , float* matrix){
    matrix[3] = x;
    matrix[7] = y;
}

//正交投影
static void orthM(float left,float right,float bottom,float top,float* matrix){
    matrix[0] = 2 / (right - left);
    matrix[3] = (right + left)/(right - left) * -1;
    matrix[5] = 2 / (top - bottom);
    matrix[7] = (top + bottom) / (top - bottom) * -1;
    matrix[10] = 1;
    matrix[11] = 1;
}





#endif //OPENGLES_STU_MATRIXUTIL_H
