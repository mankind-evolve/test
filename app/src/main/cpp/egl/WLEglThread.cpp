//
// Created by Admin on 2019/7/10.
//



#include "WLEglThread.h"
#include "../log/WLAndroidLog.h"


WLEglThread::WLEglThread() {

}

WLEglThread::~WLEglThread() {



}

//线程开始回调函数
void* eglThreadImpl(void* context){
    WLEglThread* wlEglThread = static_cast<WLEglThread *>(context);
    if(wlEglThread != NULL){
        WLEglHelper* wlEglHelper = new WLEglHelper();
        wlEglHelper->initEgl(wlEglThread->nativeWindow);
        wlEglThread->isExit = false;
        while(true) {
            if(wlEglThread->isCreate){
                LOGD("eglthread call surfacecreate");
                wlEglThread->isCreate = false;
            }

            if(wlEglThread->isChange){
                LOGD("eglthread call surfaceChange");
                wlEglThread->isChange = false;
                glViewport(0,0,1080,1920); //清屏 设置屏幕大小
                wlEglThread->isstart = true;
            }

            LOGD("draw");

            if(wlEglThread->isstart){
                glClearColor(0.0f,1.0f,1.0f,1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                wlEglHelper->swapBuffers();//渲染
            }


            usleep(1000000/60);


            if(wlEglThread->isExit){
                break;
            }

        }
    }
    return 0;

}

void WLEglThread::onSurfaceCreate(EGLNativeWindowType window) {
    if(eglThread == -1){
        isCreate = true;
        nativeWindow = window;

        pthread_create(&eglThread,NULL,eglThreadImpl,this);//创建线程
    }

}

void WLEglThread::onSurfaceChange(int width, int height) {
    isChange= true;
    surfaceWidth = width;
    surfaceHeight = height;


}
