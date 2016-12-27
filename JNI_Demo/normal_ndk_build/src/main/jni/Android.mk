

LOCAL_PATH:=$(callmy-dir)


include $(CLEAR_VARS)
LOCAL_MODULE:=JNI_ANDROID_TEST
LOCAL_SRC_FILES:=E:\work\studio_work\JNI_Study\normal_ndk_build\src/main/jni/JniTest.cpp
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=JNI_DYNAMIC_ANDROID_TEST
LOCAL_SRC_FILES:=E:\work\studio_work\JNI_Study\normal_ndk_build\src/main/jni/JNIDynamicUtils.cpp
include $(BUILD_SHARED_LIBRARY)