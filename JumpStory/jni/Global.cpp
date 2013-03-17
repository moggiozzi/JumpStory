#include "Global.h"
#include "GLHelper.h"

float worldX;
float worldY;
int maxJumpHeight;
int worldToDeviceX(float x){
  return (int)(x-worldX);
}
int worldToDeviceY(float y){
  return (int)(GLHelper::getHeight()-(y-worldY));
}

#ifdef __ANDROID__
#elif _WIN32
#ifdef _DEBUG
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#define LOGI(format,...) (LogMessage(format,__VA_ARGS__))
#define LOGW(format,...) (LogMessage(format,__VA_ARGS__))
void LogMessage ( char* format, ...) {
  static char buf [ 2048];
  va_list args;
  va_start ( args, format );
  vsprintf ( buf, format, args );
  va_end ( args );
  OutputDebugString ( buf );
  OutputDebugString ( "\n" );
}
#else
#define LOGI(...)
#define LOGW(...)
#endif

#elif __linux__
#endif

