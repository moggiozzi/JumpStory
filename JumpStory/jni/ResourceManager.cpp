#include "ResourceManager.h"

JavaVM *ResourceManager::jvm;
JNIEnv *ResourceManager::env;
AAssetManager *ResourceManager::assetManager;

uint ResourceManager::lastTextureID;
std::map<uint, Texture*> ResourceManager::textures;

jclass    ResourceManager::bitmapFactoryClass;
jmethodID ResourceManager::decodeByteArrayID;
jclass    ResourceManager::bitmapClass;
jmethodID ResourceManager::getPixelsID;

void ResourceManager::init(ANativeActivity* activity) {
	lastTextureID = 0;

	env = activity->env;
	jvm = activity->vm;
	jvm->AttachCurrentThread(&env, NULL);
	assetManager = activity->assetManager;

	bitmapFactoryClass = env->FindClass("android/graphics/BitmapFactory");
	isnull("bitmapFactory", bitmapFactoryClass);

	//decodeByteArray(byte[] data, int offset, int length)
	decodeByteArrayID = env->GetStaticMethodID(bitmapFactoryClass, "decodeByteArray",
			"([BII)Landroid/graphics/Bitmap;");
	isnull("decodeByteArrayID", decodeByteArrayID);

	bitmapClass = env->FindClass("android/graphics/Bitmap");
	isnull("bitmapClass", bitmapClass);

	//getPixels(pixels, offset, stride, x, y, width, height)
	getPixelsID = env->GetMethodID(bitmapClass, "getPixels", "([IIIIIII)V");
	isnull("getPixelsID", getPixelsID);

}

void ResourceManager::destroy() {
}

int ResourceManager::loadImage(const char *path, int format) {
	LOGI("loading %s", path);
	AAsset *asset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);
	uint bufSize = AAsset_getLength(asset);
	char* buffer = (char*) AAsset_getBuffer(asset);
	jbyteArray bytes = env->NewByteArray(bufSize);
	env->SetByteArrayRegion(bytes, 0, bufSize, (jbyte*) buffer);
	AAsset_close(asset);

	jobject bitmap = env->CallStaticObjectMethod(bitmapFactoryClass, decodeByteArrayID, bytes, 0, bufSize);
	jthrowable exc = env->ExceptionOccurred();
	if (exc != NULL) {
		LOGI("Exception in decoding file %s!", path);
		env->ExceptionDescribe();
		env->ExceptionClear();
	}
	env->DeleteLocalRef(bytes);
	if (exc != NULL || bitmap == NULL) {
		LOGI("while load %s exception occured",path);
		return -1;
	}
	AndroidBitmapInfo bitmapInfo;
	int ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);
	if (bitmap == NULL || ret != 0) {
		LOGI("%s is not loaded", path);
		return -1;
	}
	jintArray pixels = env->NewIntArray(bitmapInfo.width * bitmapInfo.height);
	env->CallVoidMethod(bitmap, getPixelsID, pixels, 0, bitmapInfo.width, 0, 0,
			bitmapInfo.width, bitmapInfo.height); // ??? CallObjectMethod
	uint dataSize = bitmapInfo.width*bitmapInfo.height;
	uint *textureData = new uint[dataSize];
	env->GetIntArrayRegion(pixels,0,dataSize,(jint*)textureData);

//todo разрбраться с порядком байтов
	for(uint i=0;i<dataSize;i++){
		textureData[i] =
				(textureData[i] & 0xff00ff00) |
				(textureData[i]<<16 & 0x00ff0000) |
				(textureData[i]>>16 & 0x000000ff);
	}
//todo

	Texture *texture = new Texture();
	texture->width = bitmapInfo.width;
	texture->height = bitmapInfo.height;
	texture->format = format;
	texture->pixels = (char*)textureData;
	lastTextureID++;
	textures.insert(std::pair<uint,Texture*>(lastTextureID,texture));
	LOGI("loading %s is OK; format:%d", path, format);
	return lastTextureID;
}

Texture* ResourceManager::getTexture(uint id) {
	std::map<uint,Texture*>::iterator it = textures.find(id);
	if (it!=textures.end())
		return it->second;
	LOGI("texture with id=%d not exist",id);
	return 0;
}

char* ResourceManager::getBytes(const char *fileName, uint &length){
	LOGI("loading %s", fileName);
	jmethodID mid;
	AAsset *asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
	if(asset==NULL){
		length=0;
		return 0;
	}
	uint bufSize = AAsset_getLength(asset);
	char* buffer = new char[bufSize];
	int ri = AAsset_read(asset, buffer, bufSize);
	if(ri==0){
		length=0;
		return 0;
		delete buffer;
	}
	length = bufSize;
	return buffer;
}


