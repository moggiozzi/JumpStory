LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -g

LOCAL_MODULE    := jumpstory
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := AudioHelper.cpp Character.cpp CollisionLayer.cpp Fps.cpp Game.cpp GameState.cpp GLHelper.cpp Global.cpp main.cpp Menu.cpp Mummy.cpp Primitives.cpp ResourceManager.cpp Sound.cpp Sprite.cpp Texture.cpp World.cpp WorldInfo.cpp

LOCAL_LDLIBS    := -llog -landroid -ljnigraphics -lEGL -lGLESv1_CM -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
