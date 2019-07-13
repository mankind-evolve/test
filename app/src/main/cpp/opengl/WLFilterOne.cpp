//
// Created by Admin on 2019/7/13.
//

#include "WLFilterOne.h"



WLFilterOne::WLFilterOne() {


}

WLFilterOne::~WLFilterOne() {

}

void WLFilterOne::onCreate() {

    vertex = "attribute vec4 v_Position;\n"
                         "attribute vec2 f_Position; \n"
                         "varying vec2 ft_Position;\n"
                         "uniform mat4 u_Matrix;\n"
                         "void main(){\n"
                         "    ft_Position = f_Position;\n"
                         "    gl_Position = v_Position * u_Matrix;\n"
                         "}";

    fragment = "precision mediump float;\n"
               "varying vec2 ft_Position;\n"
               "uniform sampler2D sTexture;\n"
               "void main(){\n"
               "    gl_FragColor = texture2D(sTexture,ft_Position);\n"
               "}";


    program = createProgrm(vertex, fragment);
    LOGD("opengl program is %d", program);
    vPostion = glGetAttribLocation(program, "v_Position"); //顶点坐标
    fPostion = glGetAttribLocation(program, "f_Position"); //纹理坐标
    sampler = glGetUniformLocation(program, "sTexture"); //2d纹理
    u_Matrix = glGetUniformLocation(program, "u_Matrix"); //坐标变换矩阵



//    rotateMatrix_z(-90,matrix); //生成旋转90的矩阵
//    scaleMatrix(0.75,matrix); //生成缩放一半的矩阵
//    tranMatrix(0.5,0,matrix);
//    orthM(-3, 1, -1, 1, matrix);

    glGenTextures(1, &textureId); //生成一个纹理，并赋值到textureId上面

    glBindTexture(GL_TEXTURE_2D, textureId);// 绑定

//    设置环绕的方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    设置过滤的方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    glBindTexture(GL_TEXTURE_2D, 0);// 解绑定
}

void WLFilterOne::onChange(int width, int height) {
    glViewport(0, 0, width, height); //设置屏幕的大小
    setMatrix(width,height); //正交矩阵设置宽高
}

void WLFilterOne::onDraw() {

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glUniformMatrix4fv(u_Matrix, 1, GL_FALSE, matrix); //赋值矩阵


    glActiveTexture(GL_TEXTURE0); //激活默认第0个纹理
    glUniform1i(sampler, 0); // 0是指纹理的类别  使用0类别，对应GL_TEXTURE0



//    绘制了个三角形
//    glUseProgram(program);
    glBindTexture(GL_TEXTURE_2D, textureId);// 绑定

    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }


    glEnableVertexAttribArray(vPostion);
    glVertexAttribPointer(vPostion, 2, GL_FLOAT, false, 8, vertexs);//用2个值代表一个点 传2


    glEnableVertexAttribArray(fPostion);
    glVertexAttribPointer(fPostion, 2, GL_FLOAT, false, 8, fragments);//用2个值代表一个点 传2



    // 一个点占8个字节，以8个字节为单位截取
//    glDrawArrays(GL_TRIANGLES,0,6); //截取6个点绘制，  两个三角形
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //截取6个点绘制，  两个三角形



    glBindTexture(GL_TEXTURE_2D, 0);// 解绑定


}

void WLFilterOne::setMatrix(int width, int height) {


    initMatrix(matrix); //初始化成单位矩阵

    float screen_r = 1.0f * width / height;
    float picture_r = 1.0f * w / h;

    if (screen_r > picture_r) { //图片高度缩放
        float r = width / (1.0 * height / h * w);
        orthM(-r,r,-1,1,matrix);
    } else {//图片宽度缩放
        float r = height / (1.0f * width / w * h);
        orthM(-1,1,-r,r,matrix);
    }
}

void WLFilterOne::setPilex(void *data, int width, int height, int length) {

    w = width;
    h= height;
    pixels = data;
    if(surface_height > 0 && surface_width > 0){
        setMatrix(surface_width,surface_height);
    }




}
