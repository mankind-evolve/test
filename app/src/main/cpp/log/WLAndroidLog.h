//
// Created by Admin on 2019/7/9.
//

#ifndef OPENGLES_STU_WLANDROIDLOG_H
#define OPENGLES_STU_WLANDROIDLOG_H


#include "android/log.h"


#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"CHENGLEI",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"CHENGLEI",FORMAT,##__VA_ARGS__);

#endif //OPENGLES_STU_WLANDROIDLOG_H
