#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_eferus_ef_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello frss55om C++";
    return env->NewStringUTF(hello.c_str());
}