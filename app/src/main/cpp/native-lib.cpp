#include <jni.h>
#include <string>


#include "egl/WLEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/WLEglThread.h"


ANativeWindow* aNativeWindow = NULL;
WLEglThread* wlEglThread = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                               jobject surface) {

    // TODO
    aNativeWindow = ANativeWindow_fromSurface(env,surface);
    wlEglThread = new WLEglThread();
    wlEglThread->onSurfaceCreate(aNativeWindow);




}extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                               jint width, jint height) {

    // TODO
    if(wlEglThread != NULL){
        wlEglThread->onSurfaceChange(width,height);
    }

}