//
// Created by Admin on 2019/7/12.
//

#ifndef OPENGLES_STU_WLSHADERUTIL_H
#define OPENGLES_STU_WLSHADERUTIL_H


#include <GLES2/gl2.h>

static int loadShaders(int shaderType, const char* code){
//    1、创建shader(着色器：顶点或片元)
    int shader = glCreateShader(shaderType);
//    2、加载shader源码并编译shader
    glShaderSource(shader,1,&code,0);
    glCompileShader(shader);
    return shader;
}

static int createProgrm(const char* vertex, const char* frament){
    int vertexShader = loadShaders(GL_VERTEX_SHADER,vertex);
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER,frament);
//    3、创建渲染程序
    int program = glCreateProgram();
//    4、讲着色器程序添加到渲染程序中
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
//    5、链接源程序
    glLinkProgram(program);
    return program;
}





#endif //OPENGLES_STU_WLSHADERUTIL_H
