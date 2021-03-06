#ifndef GLPRIMITIVES_H_
#define GLPRIMITIVES_H_

#ifndef GLOBAL_H_
#include "Global.h"
#endif
#ifndef PRIMITIVES_H_
#include "Primitives.h"
#endif
#ifndef TEXTURE_H_
#include "Texture.h"
#endif

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
  static bool isInit;
#define MAX_POINTS_COUNT 64
  static float points_[MAX_POINTS_COUNT];

  static int width;
  static int height;
  static Texture fontTexture;

  static GLfloat xToGl(int x);
  static GLfloat yToGl(int y);
public:
#ifdef __ANDROID__
  static EGLDisplay display;
  static EGLSurface surface;
  static EGLContext context;
  static bool init(ANativeWindow* window);
#elif _WIN32
  static bool init();
#elif __linux__
#endif

  static void swapBuffers();
  static void setParams();
  static void terminate();

  static int getWidth(){return width;}
  static int getHeight(){return height;}
  static void setWidth(int w){width=w;}
  static void setHeight(int h){height=h;}

  static void clear(GLfloat r=0, GLfloat g=0, GLfloat b=0, GLfloat a=1);
  static void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1);
  static void setLineWidth(GLuint w);
  static void drawCircle2d(GLfloat x, GLfloat y, GLfloat r, uint points_number=16);
  static void drawLine2d(GLint x1, GLint y1, GLint x2, GLint y2);
  static void drawCircleSector2d(GLfloat x, GLfloat y, GLfloat r, GLfloat a1, GLfloat a2, uint points_number=16);
  static void drawTriangle2d(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
  static void drawTexture(Texture* texture, int dx, int dy, int dw=-1, int dh=-1,
    int tx=0, int ty=0, int tw=-1, int th=-1);
  static void drawTexture(Texture* texture, Rect<int> &dr);
  static void drawTexture(Texture* texture, Vector2<int> &pos, float angle=0);

  static void drawText(const Vector2<int>& pos, const char* text, uint size);
  static void drawText(int x, int y, const char* text, uint size=16);
};

#endif // GLPRIMITIVES_H_
