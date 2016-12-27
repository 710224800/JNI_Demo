package com.jnitest.luyanhao.normal_ndk_build;

/**
 * Created by luyanhao on 12/20.
 */

public class JNIDynamicUtils {

    /**
     * 动态加载方式测试
     * @return
     */
    public static native String getHelloStringFromJNI();

    /**
     * 调用C++代码的方法，计算两数相加的结果返回对应的字符串
     * @return
     */
    public static native String getSumFromJNI(int i1, int i2);

    /**
     * 调用C++代码的方法，当字符串为null或长度为5时抛出异常，否则，返回该字符串的长度
     * @return
     */
    public static native int getStrLength(String str) throws NullPointerException, IllegalArgumentException;


    /**
     * 调用C++代码的方法，灰化图片
     * @param buf
     * @param w
     * @param h
     * @return
     */
    public static native int[] grayPic(int[] buf, int w, int h);

    static {
        System.loadLibrary("JNI_DYNAMIC_ANDROID_TEST");
    }

}
