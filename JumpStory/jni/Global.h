#ifndef GLOBAL_H
#define GLOBAL_H

#include <jni.h>
#include <android_native_app_glue.h>
//#include <stdlib.h>
#include <android/log.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

#define isnull(str,var) if(var==NULL)LOGI("%s is NULL",str);else LOGI("%s is OK",str);

typedef unsigned int uint;
typedef unsigned char uchar;

enum DIRECTION{UP=1,RIGHT=2,DOWN=4,LEFT=8};

#endif
