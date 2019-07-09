//
// Created by Admin on 2019/7/9.
//

#ifndef OPENGLES_STU_WLEGLHELPER_H
#define OPENGLES_STU_WLEGLHELPER_H

#include "EGL/egl.h"

class WLEglHelper {

public:
    EGLDisplay mEGLDisplay;
    EGLSurface mEGLSurface;
    EGLConfig mEGLConfig;
    EGLContext mEGLContext;


public:
    WLEglHelper(); //构造函数
    ~WLEglHelper(); //析构函数
    int initEgl(EGLNativeWindowType win);  //初始化egl
    int swapBuffers();//刷新数据
    void destoryEgl();//销毁对象

};


#endif //OPENGLES_STU_WLEGLHELPER_H
