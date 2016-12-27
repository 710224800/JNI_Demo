//
// Created by luyanhao on 12/19.
//
#include "JniTest.h"
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

/*
 * Class:     com_jnitest_luyanhao_normal_ndk_build_JniTest
 * Method:    getPackname
 * Signature: (Ljava/lang/Object;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_jnitest_luyanhao_normal_1ndk_1build_JniTest_getPackname
        (JNIEnv * env, jclass clazz, jobject obj){
    jclass mainactivity_class = env->GetObjectClass(obj);

    //MainActivity里有getPackageName这个方法 public String getPackageName()
    jmethodID mId = env->GetMethodID(mainactivity_class, "getPackageName", "()Ljava/lang/String;");

    jstring packageName = static_cast<jstring>(env->CallObjectMethod(obj, mId));

    return packageName;
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
}

