#ifndef _APP_DEF_H_
#define _APP_DEF_H_

#include <android/log.h>

#define  LOG_TAG    "SaveHostage"

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else
#define  LOGV(...)  CCLOG(__VA_ARGS__)
#define  LOGD(...)  CCLOG(__VA_ARGS__)
#define  LOGI(...)  CCLOG(__VA_ARGS__)
#define  LOGW(...)  CCLOG(__VA_ARGS__)
#define  LOGE(...)  CCLOG(__VA_ARGS__)
#endif

#endif // _APP_DEF_H_
