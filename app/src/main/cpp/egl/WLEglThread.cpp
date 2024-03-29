//
// Created by Admin on 2019/7/10.
//



#include "WLEglThread.h"
#include "../log/WLAndroidLog.h"


WLEglThread::WLEglThread() {
    pthread_mutex_init(&pthread_mutex,NULL);
    pthread_cond_init(&pthread_cond,NULL);


}

WLEglThread::~WLEglThread() {
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);

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
                wlEglThread->onCreate(wlEglThread->onCreatectx);//执行创建回调
            }

            if(wlEglThread->isChange){
                LOGD("eglthread call surfaceChange");
                wlEglThread->isChange = false;
                glViewport(0,0,wlEglThread->surfaceWidth,wlEglThread->surfaceHeight); //清屏 设置屏幕大小
                wlEglThread->onChange(wlEglThread->surfaceWidth,wlEglThread->surfaceHeight,
                        wlEglThread->onChangectx);//执行change回调
                wlEglThread->isstart =true;
            }

            LOGD("draw");

            if(wlEglThread->isstart){
//                glClearColor(0.0f,1.0f,1.0f,1.0f);
//                glClear(GL_COLOR_BUFFER_BIT);
                wlEglThread->onDraw(wlEglThread->onDrawctx); //渲染的回调
                wlEglHelper->swapBuffers();//执行渲染
            }

            if(wlEglThread->renderType == OPENGL_RENDER_AUTO ){
                usleep(1000000/60);  //帧率 60
            }else{
//                线程锁
                pthread_mutex_lock(&wlEglThread->pthread_mutex);
                pthread_cond_wait(&wlEglThread->pthread_cond,&wlEglThread->pthread_mutex);
                pthread_mutex_unlock(&wlEglThread->pthread_mutex);
            }





            if(wlEglThread->isExit){
                wlEglHelper->destoryEgl();
                delete  wlEglHelper;
                wlEglHelper = NULL;
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
    notifyRender();
}

void WLEglThread::callbackOnCreate(WLEglThread::OnCreate onCreate, void *ctx) {
    this->onCreate = onCreate;
    this->onCreatectx = ctx;
}

void WLEglThread::callbackOnChange(OnChange onChange, void *ctx) {
    this->onChange = onChange;
    this->onChangectx = ctx;


}

void WLEglThread::callbackOnDraw(OnDraw onDraw,void* ctx) {
    this->onDraw = onDraw;
    this->onDrawctx = ctx;


}

void WLEglThread:: setRenderType(int renderType) {
    this->renderType = renderType;
}

void WLEglThread::notifyRender() {
    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_signal(&pthread_cond);
    pthread_mutex_unlock(&pthread_mutex);

}

void WLEglThread::destroy() {
    isExit = true;
    notifyRender();
    pthread_join(eglThread,NULL);
    nativeWindow = NULL;
    eglThread = -1;
}
