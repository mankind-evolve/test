//
// Created by Admin on 2019/7/9.
//

#include "WLEglHelper.h"
#include "../log/WLAndroidLog.h"

WLEglHelper::WLEglHelper() {
    mEGLDisplay = EGL_NO_DISPLAY;
    mEGLSurface = EGL_NO_SURFACE;
    mEGLContext = EGL_NO_CONTEXT;
    mEGLConfig = NULL;
}

WLEglHelper::~WLEglHelper() {


}


int WLEglHelper::initEgl(EGLNativeWindowType window) {

    //1   得到默认的显示设备(就是窗口) --eglGetDisplay
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay err");
        return -1;
    }
    LOGE("eglGetDisplay success");

    //2     初始化默认显示设备   --eglInitialize()
    EGLint *version = new EGLint[2];
    if (!eglInitialize(mEGLDisplay, &version[0], &version[1])) {
        LOGE("eglInitialize err");
        return -1;
    }
    LOGE("eglInitialize success");

    //3     设置显示设备的属性
    const EGLint attribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,   //深度测试
            EGL_STENCIL_SIZE, 8, //模板测试
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,//API的等级
            EGL_NONE
    }; //颜色属性配置
    EGLint num_config;
    if (!eglChooseConfig(mEGLDisplay, attribs, NULL, 1, &num_config)) {
        LOGE("eglChooseConfig1 err");
        return -1;
    }
    LOGE("eglChooseConfig1 success");

    //4     从系统中获取对应属性的配置   --eglChooseConfig
    if (!eglChooseConfig(mEGLDisplay, attribs, &mEGLConfig, num_config, &num_config)) {
        LOGE("eglChooseConfig2 err");
        return -1;
    }
    LOGE("eglChooseConfig2 success");

    //5     创建EglContext        --eglCreateContext
    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, attrib_list);
    if (mEGLContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext err");
        return -1;
    }
    LOGE("eglCreateContext success");

    //6     创建渲染的surface        --eglCreateWindowSurface
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, window, NULL);
    if (mEGLSurface == EGL_NO_SURFACE) {
        LOGE("eglCreateWindowSurface err");
        return -1;
    }
    LOGE("eglCreateWindowSurface success");

    //7     绑定EglContext和surface到显示设备中      --eglMakeCurrent
    if (eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("eglMakeCurrent err");
        return -1;
    }
    LOGE("eglMakeCurrent success");


    LOGE("initEgl success");

    //8     刷新数据，显示渲染场景         --eglSwapBuffers
    return 0;
}


//8     刷新数据，显示渲染场景         --eglSwapBuffers
int WLEglHelper::swapBuffers() {
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        if (eglSwapBuffers(mEGLDisplay, mEGLSurface)) {
            return 0;
        }
    }
    return -1;
}

//销毁对象
void WLEglHelper::destoryEgl() {

    //7     解绑定EglContext和surface到显示设备中      --eglMakeCurrent
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mEGLDisplay, mEGLSurface);
    }
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLContext != EGL_NO_CONTEXT) {
        eglDestroyContext(mEGLDisplay, mEGLContext);
    }
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglTerminate(mEGLDisplay);
    }
}
