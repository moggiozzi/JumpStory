LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -g

LOCAL_MODULE    := jumpstory
#VisualGDBAndroid: AutoUpdateSourcesInNextLine
LOCAL_SRC_FILES := Character.cpp CollisionLayer.cpp Game.cpp GLHelper.cpp Global.cpp main.cpp Menu.cpp ResourceManager.cpp Sprite.cpp World.cpp

LOCAL_LDLIBS    := -llog -landroid -ljnigraphics -lEGL -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
