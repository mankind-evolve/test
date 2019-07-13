#include <jni.h>
#include <string>
#include "opengl/WLOpengl.h"

WLOpengl* wlOpengl = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                               jobject surface) {
    // TODO
    if(wlOpengl == NULL){
        wlOpengl = new WLOpengl();
    }
    wlOpengl->onCreateSurface(env,surface);

}
extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                               jint width, jint height) {

    if(wlOpengl!=NULL){
        wlOpengl->onChangeSurface(width,height);
    }


}extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width,
                                                         jint height, jint lenth, jbyteArray
                                                         data_) {
    jbyte * data = env->GetByteArrayElements(data_,NULL);
    if(wlOpengl != NULL){
        wlOpengl->setPilex(data,width,height,lenth);
    }
    env->ReleaseByteArrayElements(data_,data,0);

}

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceDestory(JNIEnv *env, jobject instance) {

    if(wlOpengl != NULL){
        wlOpengl->onDestorySurface();
        delete wlOpengl;
        wlOpengl = NULL;

    }


}