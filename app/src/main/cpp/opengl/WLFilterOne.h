//
// Created by Admin on 2019/7/13.
//

#ifndef OPENGLES_STU_WLFILTERONE_H
#define OPENGLES_STU_WLFILTERONE_H


#include "WLBaseOpengl.h"
#include "../matrix/MatrixUtil.h"

class WLFilterOne : public WLBaseOpengl {
public:

    GLint vPostion;
    GLint fPostion;
    GLint sampler;
    GLuint textureId;
    GLint u_Matrix;

    int w;
    int h;
    void *pixels = NULL;
    float matrix[16];


public:
    WLFilterOne();

    ~WLFilterOne();


    void onCreate();

    void onChange(int w, int h);

    void onDraw();

    void setMatrix(int width,int height);

    void setPilex(void* data,int width,int height,int length);
};


#endif //OPENGLES_STU_WLFILTERONE_H
