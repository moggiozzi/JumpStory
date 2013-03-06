#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GLES/gl.h>
#include <map>
#include "android/bitmap.h"
#include "Global.h"
#include "Helper.h"

class ResourceManager{
	static JavaVM *jvm;
	static JNIEnv *env;
	static AAssetManager *assetManager;

	static uint lastTextureID;
	static std::map<uint, Texture*> textures;

	static jclass    bitmapFactoryClass;
	static jmethodID decodeByteArrayID;
	static jclass    bitmapClass;
	static jmethodID getPixelsID;

public:
	static void init(ANativeActivity* activity);
	static void destroy();
	/**
	* Geting bitmap from file
	* @param $path
	* Path to file in assets directory
	* @return
	* Id for access to bitmap and image info (AndroidBitmapInfo structure)
	*/
	static int loadImage(const char *path, int format = GL_RGBA);
	static Texture* getTexture(uint id);
	static char* getBytes(const char *fileName, uint &length);
};

#endif
