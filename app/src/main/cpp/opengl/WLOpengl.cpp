//
// Created by Admin on 2019/7/13.
//

#include "WLOpengl.h"


void callback_SurfaceCreate(void *ctx) {

    WLOpengl *wlOpengl = static_cast<WLOpengl *>(ctx);
    if (wlOpengl != NULL) {
        if (wlOpengl->baseOpengl != NULL) {
            wlOpengl->baseOpengl->onCreate();
        }
    }
}


void callback_SurfaceOnchage(int width, int height, void *ctx) {
    WLOpengl *wlOpengl = static_cast<WLOpengl *>(ctx);
    if (wlOpengl != NULL) {
        if (wlOpengl->baseOpengl != NULL) {
            wlOpengl->baseOpengl->onChange(width, height);
        }
    }
}


void callback_SurfaceOndraw(void *ctx) {
    WLOpengl *wlOpengl = static_cast<WLOpengl *>(ctx);
    if (wlOpengl != NULL) {
        if (wlOpengl->baseOpengl != NULL) {
            wlOpengl->baseOpengl->onDraw();
        }
    }
}


WLOpengl::WLOpengl() {

}

WLOpengl::~WLOpengl() {

}

void WLOpengl::onCreateSurface(JNIEnv *env, jobject surface) {
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    wlEglThread = new WLEglThread();
    wlEglThread->setRenderType(OPENGL_RENDER_HANDLE);//设置为手动渲染
    wlEglThread->callbackOnCreate(callback_SurfaceCreate, this);
    wlEglThread->callbackOnChange(callback_SurfaceOnchage, this);
    wlEglThread->callbackOnDraw(callback_SurfaceOndraw, this);

    baseOpengl = new WLFilterOne();


    wlEglThread->onSurfaceCreate(nativeWindow);
}

void WLOpengl::onChangeSurface(int width, int height) {

    if (wlEglThread != NULL) {
        if (baseOpengl != NULL) {
            baseOpengl->surface_width = width;
            baseOpengl->surface_height = height;
        }
        wlEglThread->onSurfaceChange(width, height);
    }
}

void WLOpengl::onDestorySurface() {
    if (wlEglThread != NULL) {
        wlEglThread->destroy();
    }
    if (baseOpengl != NULL) {
        baseOpengl->destroy();
        delete baseOpengl;
        baseOpengl = NULL;
    }
    if (nativeWindow != NULL) {
        ANativeWindow_release(nativeWindow);
        nativeWindow = NULL;
    }

}

void WLOpengl::setPilex(void *data, int width, int height, int length) {
    pic_width = width;
    pic_height = height;
    pilex = malloc(length);
    memcpy(pilex, data, length);
    if (baseOpengl != NULL) {
        baseOpengl->setPilex(pilex,width,height,length);
    }

    if (wlEglThread != NULL) {
        wlEglThread->notifyRender();
    }

}

