#include <jni.h>
#include <string>


#include "egl/WLEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"


WLEglHelper* wlEglHelper = NULL;
ANativeWindow* aNativeWindow = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                               jobject surface) {

    // TODO
    aNativeWindow = ANativeWindow_fromSurface(env,surface);
    wlEglHelper = new WLEglHelper();
    wlEglHelper->initEgl(aNativeWindow);

    //opengl
    glViewport(0,0,1080,1920);
    glClearColor(1.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    wlEglHelper->swapBuffers();



}