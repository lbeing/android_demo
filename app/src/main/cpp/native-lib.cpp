#include <jni.h>
#include <string>
#include "android/log.h"
#include <sys/mman.h>

void testExecuteNativeCode(){
    uint8_t machine_code[] = {
            0x55,
            0x89, 0xe5,
            0x8b, 0x45, 0x08,
            0x83, 0xc0, 0x01,
            0x5d,
            0xc3 };
    uint8_t *executable_code = NULL;
    executable_code = (uint8_t *)mmap(0, sizeof(machine_code), PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    memcpy(executable_code, machine_code, sizeof(machine_code));
    int (*func)(int) = (int (*)(int))executable_code;
    int result = (*func)(10);
    __android_log_print(ANDROID_LOG_ERROR,"TAG","result:%d",result);
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_kuaichufa_android_1demo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    testExecuteNativeCode();
    return env->NewStringUTF(hello.c_str());
}



int inc(int a)
{
    return a + 1;
}