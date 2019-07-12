//
// Created by Admin on 2019/7/10.
//

#ifndef OPENGLES_STU_WLEGLTHREAD_H
#define OPENGLES_STU_WLEGLTHREAD_H


#include <EGL/eglplatform.h>
#include "pthread.h"
#include "android/native_window.h"
#include "WLEglHelper.h"
#include <unistd.h>
#include <GLES2/gl2.h>



#define OPENGL_RENDER_AUTO 1
#define OPENGL_RENDER_HANDLE 2

class WLEglThread {
public:
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isstart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;


//    创建的回调
    typedef void(*OnCreate)(void *);

    OnCreate onCreate;
    void *onCreatectx;

//    改变的回调
    typedef void(*OnChange)(int w, int h, void *);

    OnChange onChange;
    void *onChangectx;

//    绘制的回调
    typedef void (*OnDraw)(void *);

    OnDraw onDraw;
    void *onDrawctx;


    int renderType = OPENGL_RENDER_AUTO;

    pthread_mutex_t pthread_mutex;
    pthread_cond_t pthread_cond;


public:
    WLEglThread();

    ~WLEglThread();

    void onSurfaceCreate(EGLNativeWindowType window);

    void onSurfaceChange(int width, int height);

    void callbackOnCreate(OnCreate onCreate1, void *ctx);

    void callbackOnChange(OnChange onChange, void *ctx);

    void callbackOnDraw(OnDraw onDraw, void *ctx);

    void setRenderType(int renderType);

    void notifyRender();
};


#endif //OPENGLES_STU_WLEGLTHREAD_H
