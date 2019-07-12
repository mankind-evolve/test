#include <jni.h>
#include <string>


#include "egl/WLEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/WLEglThread.h"
#include "log/WLAndroidLog.h"
#include "shaderutil/WLShaderUtil.h"


ANativeWindow *aNativeWindow = NULL;
WLEglThread *wlEglThread = NULL;


const char *vertex = "attribute vec4 v_Position;\n"
                     "attribute vec2 f_Position; \n"
                     "varying vec2 ft_Position;\n"
                     "void main(){\n"
                     "    ft_Position = f_Position;\n"
                     "    gl_Position = v_Position;\n"
                     "}";
const char *fragment = "precision mediump float;\n"
                       "varying vec2 ft_Position;\n"
                       "uniform sampler2D sTexture;\n"
                       "void main(){\n"
                       "    gl_FragColor = texture2D(sTexture,ft_Position);\n"
                       "}";


int program;
GLint vPostion;
GLint fPostion;
GLint sampler;
GLuint textureId;
void *pixels = NULL;


int w;
int h;

//顶点坐标
float vertexs[] = {
        1, -1,
        1, 1,
        -1, -1,
        -1, 1
};

//纹理坐标
float fragments[] = {
        1, 1,
        1, 0,
        0, 1,
        0, 0
};


void callback_SurfaceCreate(void *ctx) {
    LOGD("callback_SurfaceCreate");
    WLEglThread *wlEglThread1 = static_cast<WLEglThread *>(ctx);

    program = createProgrm(vertex, fragment);
    LOGD("opengl program is %d", program);
    vPostion = glGetAttribLocation(program, "v_Position"); //顶点坐标
    fPostion = glGetAttribLocation(program, "f_Position"); //纹理坐标
    sampler = glGetUniformLocation(program, "sTexture"); //2d纹理

    glGenTextures(1, &textureId); //生成一个纹理，并赋值到textureId上面

    glBindTexture(GL_TEXTURE_2D, textureId);// 绑定

//    设置环绕的方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    设置过滤的方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    glBindTexture(GL_TEXTURE_2D, 0);// 解绑定

}

void callback_SurfaceOnchage(int w, int h, void *ctx) {
    LOGD("callback_SurfaceOnchage");
    WLEglThread *wlEglThread1 = static_cast<WLEglThread *>(ctx);
    glViewport(0, 0, w, h);


}

void callback_SurfaceOndraw(void *ctx) {
    LOGD("callback_SurfaceOndraw");
    WLEglThread *wlEglThread1 = static_cast<WLEglThread *>(ctx);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glActiveTexture(GL_TEXTURE0); //激活默认第0个纹理
    glUniform1i(sampler,0); // 0是指纹理的类别  使用0类别，对应GL_TEXTURE0



//    绘制了个三角形
    glUseProgram(program);
    glBindTexture(GL_TEXTURE_2D, textureId);// 绑定
    glEnableVertexAttribArray(vPostion);
    glVertexAttribPointer(vPostion, 2, GL_FLOAT, false, 8, vertexs);//用2个值代表一个点 传2


    glEnableVertexAttribArray(fPostion);
    glVertexAttribPointer(fPostion, 2, GL_FLOAT, false, 8, fragments);//用2个值代表一个点 传2



    // 一个点占8个字节，以8个字节为单位截取
//    glDrawArrays(GL_TRIANGLES,0,6); //截取6个点绘制，  两个三角形
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //截取6个点绘制，  两个三角形



    glBindTexture(GL_TEXTURE_2D, 0);// 解绑定
}

extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance,
                                                               jobject surface) {

    // TODO
    aNativeWindow = ANativeWindow_fromSurface(env, surface);
    wlEglThread = new WLEglThread();
    wlEglThread->setRenderType(OPENGL_RENDER_HANDLE);//设置为手动渲染
    wlEglThread->callbackOnCreate(callback_SurfaceCreate, wlEglThread);
    wlEglThread->callbackOnChange(callback_SurfaceOnchage, wlEglThread);
    wlEglThread->callbackOnDraw(callback_SurfaceOndraw, wlEglThread);


    wlEglThread->onSurfaceCreate(aNativeWindow);


}extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance,
                                                               jint width, jint height) {

    // TODO
    if (wlEglThread != NULL) {
        wlEglThread->onSurfaceChange(width, height);
        usleep(1000000);
        wlEglThread->notifyRender();
    }

}extern "C"
JNIEXPORT void JNICALL
Java_videoeditor_videoeffect_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width,
                                                         jint height, jint lenth, jbyteArray
                                                         data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    w = width;
    h = height;

    pixels = malloc(lenth);
    memcpy(pixels,data,lenth);

    env->ReleaseByteArrayElements(data_, data, 0);
}