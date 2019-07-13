//
// Created by Admin on 2019/7/13.
//

#ifndef OPENGLES_STU_WLOPENGL_H
#define OPENGLES_STU_WLOPENGL_H

#include "../egl/WLEglThread.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "WLBaseOpengl.h"
#include "WLFilterOne.h"



class WLOpengl {
public:
    WLEglThread *wlEglThread = NULL;
    ANativeWindow *nativeWindow = NULL;
    WLBaseOpengl *baseOpengl = NULL;

    int pic_width;
    int pic_height;
    void* pilex = NULL;


public:
    WLOpengl();
    ~WLOpengl();
    void onCreateSurface(JNIEnv *env,jobject surface);

    void onChangeSurface(int width,int height);

    void onDestorySurface();

    void setPilex(void* data,int width,int height,int length);

};


#endif //OPENGLES_STU_WLOPENGL_H
