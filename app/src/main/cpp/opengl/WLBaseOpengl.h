//
// Created by Admin on 2019/7/13.
//

#ifndef OPENGLES_STU_WLBASEOPENGL_H
#define OPENGLES_STU_WLBASEOPENGL_H


#include <GLES2/gl2.h>
#include <cstring>
#include "../log/WLAndroidLog.h"
#include "../shaderutil/WLShaderUtil.h"

class WLBaseOpengl {

public :

    int surface_width;
    int surface_height;

    char *vertex;
    char *fragment;

    float* vertexs;
    float* fragments;

    GLint program;


public:
    WLBaseOpengl();
    ~WLBaseOpengl();

    virtual void onCreate();
    virtual void onChange(int w,int h);
    virtual void onDraw();

    virtual void destroy();

    virtual void setPilex(void* data,int width,int height,int length);

};


#endif //OPENGLES_STU_WLBASEOPENGL_H

