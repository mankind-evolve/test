//
// Created by Admin on 2019/7/10.
//

#ifndef OPENGLES_STU_WLEGLTHREAD_H
#define OPENGLES_STU_WLEGLTHREAD_H


#include <EGL/eglplatform.h>
#include "pthread.h"
#include "WLEglHelper.h"
#include <unistd.h>
#include <GLES2/gl2.h>\




class WLEglThread {
public:
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isstart = false;

    bool  surfaceWidth = 0 ;
    bool  surfaceHeight = 0 ;

public:
    WLEglThread();
    ~WLEglThread();

    void onSurfaceCreate(EGLNativeWindowType window);
    void onSurfaceChange(int width ,int height);
};


#endif //OPENGLES_STU_WLEGLTHREAD_H
