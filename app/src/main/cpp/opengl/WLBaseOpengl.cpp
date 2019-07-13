//
// Created by Admin on 2019/7/13.
//


#include "WLBaseOpengl.h"

WLBaseOpengl::WLBaseOpengl() {

    vertexs = new float[8];
    fragments = new float[8];

    float v[] = {
            1, -1,
            1, 1,
            -1, -1,
            -1, 1
    };
    memcpy(vertexs,v, sizeof(v));


    float f[] = {
            1, 1,
            1, 0,
            0, 1,
            0, 0
    };
    memcpy(fragments,f, sizeof(f));

}

WLBaseOpengl::~WLBaseOpengl() {
        delete [] vertexs;
        delete [] fragments;

}

void WLBaseOpengl::onCreate() {


}

void WLBaseOpengl::onChange(int w, int h) {

}

void WLBaseOpengl::onDraw() {

}

void WLBaseOpengl::destroy() {

}

void WLBaseOpengl::setPilex(void *data, int width, int height, int length) {

}
