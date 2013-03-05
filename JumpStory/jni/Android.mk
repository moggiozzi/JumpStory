LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -g

LOCAL_MODULE    := jumpstory
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := jumpstory.cpp Global.cpp GLHelper.cpp ResourceManager.cpp Game.cpp Menu.cpp World.cpp Sprite.cpp

LOCAL_LDLIBS    := -llog -landroid -ljnigraphics -lEGL -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
