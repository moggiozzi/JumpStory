#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/egl.h>
#include <math.h>
#include "GLhelper.h"
#include "Global.h"

#define gradToRad(x) (x * 0.0174532925199)
#define radToGrad(x) (x * 57.295779513082)
#define isglerr(str) {int err; if((err=glGetError())!=GL_NO_ERROR) LOGI("%s error 0x%X", str, err);}

// Без объявления статичных полей получим error: undefined refernece
EGLDisplay GLHelper::display;
EGLSurface GLHelper::surface;
EGLContext GLHelper::context;

float GLHelper::width;
float GLHelper::height;
float GLHelper::myWidth;
float GLHelper::myHeight;
float GLHelper::points_[MAX_POINTS_COUNT];

mTexture *GLHelper::fontTexture;

int GLHelper::init(ANativeWindow* window){
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);
    surface = eglCreateWindowSurface(display, config, window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }
    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
//	if(w>h){
//	    myWidth  = (float)w/h*2;
//	    myHeight = 2.0;
//		glScalef((float)h/w,1,1);
//	}else{
//	   	myWidth  = 2.0;
//	    myHeight = (float)h/w*2;
//	    glScalef(1,(float)w/h,1);
//	}
	width  = w;
	height = h;
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.5,0.5,0,1);
    return 0;
}

void GLHelper::terminate(){
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}


//Vector2f GLHelper::devToGl(uint x, uint y){
//	Vector2f coords;
//	coords.x = (float)(2*x-width )/width ;
//	coords.y = (float)(height-2*y)/height;
//	return coords;
//}
//
//Vector2f GLHelper::devToMy(uint x, uint y){
//	Vector2f coords;
//	coords.x = (float)(x-width/2)*myWidth/width;
//	coords.y = (float)(height/2-y)*myHeight/height;
//	return coords;
//}
//
//Vector2f GLHelper::myToGl(float x, float y){
//	Vector2f coords;
//	coords.x = (float)2*x/myWidth;
//	coords.y = (float)2*y/myHeight;
//	return coords;
//}


void GLHelper::setBuffer(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer( 2, GL_FLOAT, 0, points_ ); //2 координаты на точку
}

void GLHelper::clear(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLHelper::setColor(float r, float g, float b, float a){
	glColor4f(r,g,b,a);
}
void GLHelper::setLineWidth(float w){
	glLineWidth(w);
}

void GLHelper::drawLine2df(double x1, double y1, double x2, double y2){
	GLHelper::setBuffer();
	points_[0]=x1;
	points_[1]=y1;
	points_[2]=x2;
	points_[3]=y2;
	glDrawArrays( GL_LINES, 0, 2 );
}

void GLHelper::drawLine2d(int x1, int y1, int x2, int y2){
	GLHelper::setBuffer();
	points_[0]=xToGl(x1);
	points_[1]=yToGl(y1);
	points_[2]=xToGl(x2);
	points_[3]=yToGl(y2);
	glDrawArrays( GL_LINES, 0, 2 );
}


void GLHelper::drawCircle2d(float x, float y, float r, uint points_number){
	if((points_number+2)*2>MAX_POINTS_COUNT) points_number=(MAX_POINTS_COUNT-2)/2;
	points_[0]=x; //центр круга
	points_[1]=y;
	float angle;
	for(unsigned int i=0; i<points_number+1; i++){	//+1 замыкающая точка
		angle = 2*M_PI*i/points_number;
		points_[i*2+2] = x + r*cos(angle);
		points_[i*2+3] = y + r*sin(angle);
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, points_number+2 );
}

void GLHelper::drawCircleSector2d(float x, float y, float r, float a1, float a2, uint points_number){
	if((points_number+2)*2>MAX_POINTS_COUNT) points_number=(MAX_POINTS_COUNT-2)/2;
	points_[0]=x; //центр круга
	points_[1]=y;
	a1 = gradToRad(a1);
	a2 = gradToRad(a2);
	float angle = a1;
	float angleStep;
	if( a2 > a1 )
		angleStep = (a2-a1)/points_number;
	else
		angleStep = (2*M_PI+a2-a1)/points_number;
	for(uint i=0; i<points_number+1; i++){
		points_[i*2+2] = x + r*cos(angle);
		points_[i*2+3] = y + r*sin(angle);
		angle += angleStep;
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, points_number+2 );
}

void GLHelper::drawTriangle2d(float x1, float y1, float x2, float y2, float x3, float y3){
	points_[0]=x1;
	points_[1]=y1;
	points_[2]=x2;
	points_[3]=y2;
	points_[4]=x3;
	points_[5]=y3;
	glDrawArrays( GL_TRIANGLE_FAN, 0, 3 );
}

void GLHelper::drawTexturef(mTexture* texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height,
		GLint tx, GLint ty, GLint tw, GLint th){
	if(tw==-1){
		tw = texture->width;
		th = texture->height;
	}
	GLuint texName;
	isglerr("Eror glGenTextures");
	glGenTextures(1, &texName);
	glEnable (GL_TEXTURE_2D);
	isglerr("Eror glEnable(GL_TEXTURE_2D)");
	glEnable(GL_BLEND);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ALPHA);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_SRC_ALPHA);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	LOGI("f%d",texture->format);
	glTexImage2D(GL_TEXTURE_2D, 0, texture->format, texture->width, texture->height, 0,
			texture->format, GL_UNSIGNED_BYTE, texture->pixels);
	isglerr("Eror loading texture into OpenGL.");
	points_[0] = x;			points_[1] = y-height;
	points_[2] = x;			points_[3] = y;
	points_[4] = x + width; points_[5] = y;
	points_[6] = x + width; points_[7] = y-height;
	glVertexPointer(2, GL_FLOAT, 0, points_);
	float pp[] = {
			(float)tx/texture->width,     (float)(ty+th)/texture->height, //0,0,
			(float)tx/texture->width,     (float)ty/texture->height,      //0,1
			(float)(tx+tw)/texture->width,(float)ty/texture->height,      //1,1
			(float)(tx+tw)/texture->width,(float)(ty+th)/texture->height, //1,0,
	};
	glTexCoordPointer(2, GL_FLOAT, 0, pp);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GLHelper::drawTexture(mTexture* texture, int dx, int dy, int dw, int dh,
		int tx, int ty, int tw, int th){
	if(tw==-1){
		tw = texture->width;
		th = texture->height;
	}
	if(dw=-1){
		dw=texture->width;
		dh=texture->height;
	}
	if (texture->isGenTexNameGl) {
		glGenTextures(1, &texture->texNameGl);
		texture->isGenTexNameGl = true;
		isglerr("Eror glGenTextures");
	}
	glEnable (GL_TEXTURE_2D);
	isglerr("Eror glEnable(GL_TEXTURE_2D)");
	glEnable(GL_BLEND);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ALPHA);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_SRC_ALPHA);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texture->texNameGl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	LOGI("f%d",texture->format);
	glTexImage2D(GL_TEXTURE_2D, 0, texture->format, texture->width, texture->height, 0,
			texture->format, GL_UNSIGNED_BYTE, texture->pixels);
	isglerr("Eror loading texture into OpenGL.");
	points_[0] = xToGl(dx); 			points_[1] = yToGl(dy+dh);
	points_[2] = xToGl(dx);				points_[3] = yToGl(dy);
	points_[4] = xToGl(dx+dw);	points_[5] = yToGl(dy);
	points_[6] = xToGl(dx+dw); 	points_[7] = yToGl(dy+dh);
	glVertexPointer(2, GL_FLOAT, 0, points_);
	float pp[] = {
			(float)tx/texture->width,     (float)(ty+th)/texture->height, //0,0,
			(float)tx/texture->width,     (float)ty/texture->height,      //0,1
			(float)(tx+tw)/texture->width,(float)ty/texture->height,      //1,1
			(float)(tx+tw)/texture->width,(float)(ty+th)/texture->height, //1,0,
	};
	glTexCoordPointer(2, GL_FLOAT, 0, pp);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


void GLHelper::drawText(float x, float y, const char* text, float size){
	uint len = strlen(text);
	uint fontTextureSize = 256;
	uint glyphSize = 16;
	float textureCoords[8];

	GLuint texName;
	glGenTextures(1, &texName);
	isglerr("Eror glGenTextures");
	glEnable (GL_TEXTURE_2D);
	isglerr("Error glEnable(GL_TEXTURE_2D)");
	glEnable(GL_BLEND);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ALPHA);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_SRC_ALPHA);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//LOGI("f%d",texture->format);
	glTexImage2D(GL_TEXTURE_2D, 0, fontTexture->format, fontTexture->width, fontTexture->height, 0,
			fontTexture->format, GL_UNSIGNED_BYTE, fontTexture->pixels);
	isglerr("Eror loading texture into OpenGL.");
	glVertexPointer(2, GL_FLOAT, 0, points_);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);

	int i,j;
	for(uint k=0;k<len;k++){
		i=text[k]/16;
		j=text[k]%16;
		textureCoords[0]=(float)j*glyphSize/fontTextureSize;	textureCoords[1]=(float)i*glyphSize/fontTextureSize;
		textureCoords[2]=(float)j*glyphSize/fontTextureSize;	textureCoords[3]=(float)(i+1)*glyphSize/fontTextureSize;
		textureCoords[4]=(float)(j+1)*glyphSize/fontTextureSize;textureCoords[5]=(float)(i+1)*glyphSize/fontTextureSize;
		textureCoords[6]=(float)(j+1)*glyphSize/fontTextureSize;textureCoords[7]=(float)i*glyphSize/fontTextureSize;

		points_[0] = x+k*size;	   points_[1] = y;
		points_[2] = x+k*size;	   points_[3] = y-size;
		points_[4] = x+(k+1)*size; points_[5] = y-size;
		points_[6] = x+(k+1)*size; points_[7] = y;
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	}
}
