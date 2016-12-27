package com.jnitest.luyanhao.normal_ndk_build;

/**
 * Created by luyanhao on 12/19.
 */

public class JniTest {

    public static native String getPackname(Object o);

    static {
        System.loadLibrary("JNI_ANDROID_TEST");
    }
}
