#include <jni.h>
#include <string>


#include "egl/WLEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/WLEglThread.h"
#include "log/WLAndroidLog.h"
#include "shaderutil/WLShaderUtil.h"


ANativeWindow* aNativeWindow = NULL;
WLEglThread* wlEglThread = NULL;

const char* vertex="attribute vec2 a_position;\n"
                    "\n"
                    "void main(){\n"
                    "   gl_Position = a_position;\n"
                    "}";
const char* fragment = "precision mediump float;\n"
                       "\n"
                       "void main(){\n"
                       "    gl_FragColor = vec4(1f,0f,0f,1f);\n"
                       "}";


void callback_SurfaceCreate(void* ctx){
    LOGD("callback_SurfaceCreate");
    WLEglThread* wlEglThread1 = static_cast<WLEglThread *>(ctx);
}

void callback_SurfaceOnchage(int w, int h ,void* ctx){
    LOGD("callback_SurfaceOnchage");
    WLEglThread* wlEglThread1 = static_cast<WLEglThread *>(ctx);
    glViewport(0,0,w,h);


}

void callback_SurfaceOndraw(void* ctx){
    LOGD("callback_SurfaceOndraw");
    WLEglThread* wlEglThread1 = static_cast<WLEglThread *>(ctx);
    glClearColor(1.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                               jobject surface) {

    // TODO
    aNativeWindow = ANativeWindow_fromSurface(env,surface);
    wlEglThread = new WLEglThread();
//    wlEglThread->setRenderType(OPENGL_RENDER_HANDLE);//设置为手动渲染
    wlEglThread->callbackOnCreate(callback_SurfaceCreate,wlEglThread);
    wlEglThread->callbackOnChange(callback_SurfaceOnchage,wlEglThread);
    wlEglThread->callbackOnDraw(callback_SurfaceOndraw,wlEglThread);


    wlEglThread->onSurfaceCreate(aNativeWindow);

    int program = createProgrm(vertex,fragment);
    LOGD("opengl program is %d",program);



}extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                               jint width, jint height) {

    // TODO
    if(wlEglThread != NULL){
        wlEglThread->onSurfaceChange(width,height);
    }

}