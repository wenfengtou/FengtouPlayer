#include <jni.h>
#include <string>


extern "C" JNIEXPORT jstring

JNICALL
Java_com_wenfengtou_ffmpeglib_HelloJniHelper_hello(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
