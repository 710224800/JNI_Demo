//
// Created by luyanhao on 12/20.
//

#include <stdio.h>
#include <jni.h>
#include <stdlib.h>


extern "C"
//C++层 native函数
//动态加载测试1
__attribute ((visibility ("default")))
jstring native_hello(JNIEnv *env, jclass clz) {
    return env->NewStringUTF("Hello java, this is C++. ---jni动态加载方式");
}

//计算两个数的值
__attribute ((visibility ("default")))
jstring calcSum(JNIEnv *env, jclass clazz, jint i1, jint i2) {
    char result[50];
    sprintf(result, " this is string from jni. result is %d", (i1 + i2));
    return env->NewStringUTF(result);
}

//异常处理测试
__attribute ((visibility ("default")))
jint getLengthOfStr(JNIEnv *env, jclass clazz, jstring str) {
    if (str == NULL) {
        // 抛出空指针异常
        jclass clz = env->FindClass("java/lang/NullPointerException");
        jmethodID methodId = env->GetMethodID(clz, "<init>", "()V");
        jthrowable throwable = (jthrowable) env->NewObject(clz, methodId);
        env->Throw(throwable);
    } else {
        jint len = env->GetStringUTFLength(str);
        if (len == 5) {
            // 抛出IllegalArgumentException异常
            jclass illegalArgumentException = env->FindClass("java/lang/IllegalArgumentException");
            env->ThrowNew(illegalArgumentException,
                          "this is IllegalArgumentException error form C++, because the str length is 5");
        } else {
            return len;
        }
    }
    return 0;
}

// C++灰化图片的方法
__attribute ((visibility ("default")))
jintArray nativeGrayPic(JNIEnv *env, jclass clazz, jintArray buf, jint w, jint h) {
    jint *cbuf;
    cbuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if (cbuf == NULL) {
        return 0; /* exception occurred */
    }
    jint alpha = 0xFF << 24;
    for (jint i = 0; i < h; i++) {
        for (jint j = 0; j < w; j++) {
            // 获得像素的颜色
            jint color = cbuf[w * i + j];
            jint red = ((color & 0x00FF0000) >> 16);
            jint green = ((color & 0x0000FF00) >> 8);
            jint blue = color & 0x000000FF;
            color = (red + green + blue) / 3;
            color = alpha | (color << 16) | (color << 8) | color;
            cbuf[w * i + j] = color;
        }
    }
    jint size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, cbuf);
    env->ReleaseIntArrayElements(buf, cbuf, 0);
    return result;
}


/**
 * JNINativeMethod由三部分组成,可添加多组对应:
 * (1)Java中的函数名;
 * (2)函数签名,格式为(输入参数类型)返回值类型;
 *  ()Ljava/lang/String; ()表示无参，Ljava/lang/String;表示返回String，在对象类名（包括包名，‘/’间隔）前面加L，分号结尾
 * (3)native函数名
 */
static JNINativeMethod gMethods[] = {{"getHelloStringFromJNI", "()Ljava/lang/String;",   (void *) native_hello},
                                     {"getSumFromJNI",         "(II)Ljava/lang/String;", (void *) calcSum},
                                     {"getStrLength",          "(Ljava/lang/String;)I",  (void *) getLengthOfStr},
                                     {"grayPic",               "([III)[I",               (void *) nativeGrayPic}};

//System.loadLibrary过程中会自动调用JNI_OnLoad，在此进行动态注册
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_FALSE;

    //获取env指针
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    if (env == NULL) {
        return result;
    }
    //获取类引用，写类的全路径（包名+类名）。FindClass等JNI函数将在后面讲解
    jclass clazz = env->FindClass("com/jnitest/luyanhao/normal_ndk_build/JNIDynamicUtils");
    if (clazz == NULL) {
        return result;
    }
    //注册方法
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) < 0) {
        return result;
    }
    //成功
    result = JNI_VERSION_1_6;
    return result;
}