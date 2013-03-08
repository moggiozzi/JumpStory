#ifndef GLHELPER_H_
#define GLHELPER_H_

#include "Global.h"
#include "Helper.h"

#ifdef __ANDROID__
#define GL_GLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <GLES/gl.h>
#elif _WIN32
#include <windows.h>
#include <gl/gl.h>
#elif __linux__
#endif

class GLHelper{
#define MAX_POINTS_COUNT 64
  static float points_[MAX_POINTS_COUNT];

  static uint width;
  static uint height;
  static Texture fontTexture;

  inline static GLfloat xToGl(int x) { return static_cast<GLfloat>(((double)x/GLHelper::width-0.5)*2.0); }
  inline static GLfloat yToGl(int y) { return static_cast<GLfloat>(((double)(height-y)/GLHelper::height-0.5)*2.0); }
public:
#ifdef __ANDROID__
  static EGLDisplay display;
  static EGLSurface surface;
  static EGLContext context;
  static bool init(ANativeWindow* window);
#elif _WIN32
  static HWND hWnd;
  static HDC hDC;
  static HGLRC hRC;
  static bool init(HWND hWnd);
#elif __linux__
#endif

  static void swapBuffers();
  static void terminate();

  static uint getWidth(){return width;}
  static uint getHeight(){return height;}

  static void clear(GLfloat r=0, GLfloat g=0, GLfloat b=0, GLfloat a=1);
  static void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
  static void setLineWidth(GLuint w);
  static void drawCircle2d(GLfloat x, GLfloat y, GLfloat r, uint points_number=16);
  static void drawLine2d(GLint x1, GLint y1, GLint x2, GLint y2);
  static void drawCircleSector2d(GLfloat x, GLfloat y, GLfloat r, GLfloat a1, GLfloat a2, uint points_number=16);
  static void drawTriangle2d(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
  static void drawTexture(Texture* texture, int dx, int dy, int dw=-1, int dh=-1,
    int tx=0, int ty=0, int tw=-1, int th=-1);
  //static void drawText(int x, int y, const char* text, uint size=16);
};

#endif // GLHELPER_H_
