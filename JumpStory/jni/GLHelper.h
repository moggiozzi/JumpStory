#ifndef GLHELPER_H
#define GLHELPER_H

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "Global.h"
#include "Helper.h"

#define MAX_POINTS_COUNT 64

class GLHelper{
	static float points_[MAX_POINTS_COUNT];

	static float width;		// размеры дисплея в координатах openGL
	static float height;	// по меньшей стороне будет 1.0, для другой >1.0

	static float myWidth ;
	static float myHeight;

	static mTexture *fontTexture;

	static void setBuffer();
	inline static double xToGl(int x) { return (double)(x/GLHelper::width-0.5)*2.0; }
	inline static double yToGl(int y) { return (double)((height-y)/GLHelper::height-0.5)*2.0; }
public:
    static EGLDisplay display;
    static EGLSurface surface;
    static EGLContext context;

	static int init(ANativeWindow* window);
	static void terminate();

//	static Vector2f devToGl(uint x, uint y); // конвертация координат (Device <-> My <-> GL)
//	static Vector2f devToMy(uint x, uint y);
//	static Vector2f myToGl (float x, float y);
	//static Coord2d glToMy (float x, float y);

	static float getWidth(){return myWidth;}
	static float getHeight(){return myHeight;}

	static void setFontTexture(mTexture* ft) { fontTexture = ft; }

	static void clear(float r=0, float g=0, float b=0, float a=1);
	static void setColor(float r, float g, float b, float a=1);
	static void setLineWidth(float w);
	static void drawCircle2d(float x, float y, float r, uint points_number=16);
	static void drawLine2d(int x1, int y1, int x2, int y2);
	static void drawLine2df(double x1, double y1, double x2, double y2);
	static void drawCircleSector2d(float x, float y, float r, float a1, float a2, uint points_number=16);
	static void drawTriangle2d(float x1, float y1, float x2, float y2, float x3, float y3);
	static void drawTexture();
	static void drawTexture(mTexture* texture, int dx, int dy, int dw=-1, int dh=-1,
			int tx=0, int ty=0, int tw=-1, int th=-1);
	static void drawTexturef(mTexture* texture, GLfloat x, GLfloat y, GLfloat width=1, GLfloat height=1,
			GLint tx=0, GLint ty=0, GLint tw=-1, GLint th=-1);

	static void drawText(float x, float y, const char* text, float size=0.125);
};

#endif
