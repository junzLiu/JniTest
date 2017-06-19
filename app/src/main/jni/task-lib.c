#include <jni.h>
#include <string.h>


jstring ByteArrayToString(JNIEnv *env,jbyteArray jbyteArray1);

JNIEXPORT jstring JNICALL
Java_lzj_com_jnitest_MainActivity_getSmStr(JNIEnv *env, jobject instance) {

    // TODO

    return (*env)->NewStringUTF(env,"hello the friend!");
}

JNIEXPORT jint JNICALL
Java_lzj_com_jnitest_MainActivity_getCount(JNIEnv *env, jobject instance) {

    // TODO
    return 1;
}

JNIEXPORT jstring JNICALL
Java_lzj_com_jnitest_JniBridge_getJinStr(JNIEnv *env, jobject instance) {

    // TODO


    return (*env)->NewStringUTF(env,"zencode");
}

JNIEXPORT void JNICALL
Java_lzj_com_jnitest_JniBridge_checkSignative(JNIEnv *env, jclass type, jobject instance) {

    // TODO

}

jstring ByteArrayToString(JNIEnv *env,jbyteArray jbyteArray1){
    jclass string = (*env)->FindClass(env,"java/lang/String");
    jmethodID  mid = (*env)->GetMethodID(env,string,"<init>","([BLjava/lang/String;)V");
    jstring encoding = (*env)->NewStringUTF(env,"utf-8");
    return (jstring)(*env)->NewObject(env,string,mid,jbyteArray1,encoding);

}

jstring ToMd5(JNIEnv *env, jbyteArray source) {
    // MessageDigest类
    jclass classMessageDigest = (*env)->FindClass(env,"java/security/MessageDigest");
    // MessageDigest.getInstance()静态方法
    jmethodID midGetInstance = (*env)->GetStaticMethodID(env,classMessageDigest, "getInstance",
                                                      "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    // MessageDigest object
    jobject objMessageDigest = (*env)->CallStaticObjectMethod(env,classMessageDigest, midGetInstance,
                                                            (*env)->NewStringUTF(env,"md5"));

    // update方法，这个函数的返回值是void，写V
    jmethodID midUpdate = (*env)->GetMethodID(env,classMessageDigest, "update", "([B)V");
    (*env)->CallVoidMethod(env,objMessageDigest, midUpdate, source);

    // digest方法
    jmethodID midDigest = (*env)->GetMethodID(env,classMessageDigest, "digest", "()[B");
    jbyteArray objArraySign = (jbyteArray) (*env)->CallObjectMethod(env,objMessageDigest, midDigest);

    jsize intArrayLength = (*env)->GetArrayLength(env,objArraySign);
    jbyte *byte_array_elements = (*env)->GetByteArrayElements(env,objArraySign, NULL);
    size_t length = (size_t) intArrayLength * 2 + 1;
    char *char_result = (char *) malloc(length);
    memset(char_result, 0, length);

    // 将byte数组转换成16进制字符串，发现这里不用强转，jbyte和unsigned char应该字节数是一样的
    ByteToHexStr((const char *) byte_array_elements, char_result, intArrayLength);
    // 在末尾补\0
    *(char_result + intArrayLength * 2) = '\0';

    jstring stringResult = (*env)->NewStringUTF(env,char_result);
    // release
    (*env)->ReleaseByteArrayElements(env,objArraySign, byte_array_elements, JNI_ABORT);
    // 释放指针使用free
    free(char_result);

    return stringResult;
}

void ByteToHexStr(const char *source, char *dest, int sourceLen) {
    short i;
    char highByte, lowByte;

    for (i = 0; i < sourceLen; i++) {
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f;
        highByte += 0x30;

        if (highByte > 0x39) {
            dest[i * 2] = highByte + 0x07;
        } else {
            dest[i * 2] = highByte;
        }

        lowByte += 0x30;
        if (lowByte > 0x39) {
            dest[i * 2 + 1] = lowByte + 0x07;
        } else {
            dest[i * 2 + 1] = lowByte;
        }
    }
}

JNIEXPORT jstring JNICALL
Java_lzj_com_jnitest_JniBridge_getSignativeStr(JNIEnv *env, jclass type, jobject instance) {

    // TODO
//获取Context类
    jclass cls = (*env)->GetObjectClass(env,instance);
    //得到getPackageManger方法的ID
    jmethodID mid = (*env)->GetMethodID(env,cls,"getPackageManager","()Landroid/content/pm/PackageManager;");
    //获得应用包的管理器
    jobject pm = (*env)->CallObjectMethod(env,instance,mid);

    //获得getPackageName方法的ID
    mid = (*env)->GetMethodID(env,cls,"getPackageName","()Ljava/lang/String;");
    //获取当前应用包
    jstring packageName = (jstring)(*env)->CallObjectMethod(env,instance,mid);

    // 获得PackageManager类
    cls = (*env)->GetObjectClass(env,pm);
    // 得到getPackageInfo方法的ID
    mid = (*env)->GetMethodID(env,cls, "getPackageInfo",
                           "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    // 获得应用包的信息
    jobject packageInfo = (*env)->CallObjectMethod(env,pm, mid, packageName, 0x40); //GET_SIGNATURES = 64;
    // 获得PackageInfo 类
    cls = (*env)->GetObjectClass(env,packageInfo);
    // 获得签名数组属性的ID
    jfieldID fid = (*env)->GetFieldID(env,cls, "signatures", "[Landroid/content/pm/Signature;");
    // 得到签名数组
    jobjectArray signatures = (jobjectArray) (*env)->GetObjectField(env,packageInfo, fid);
    // 得到签名
    jobject signature = (*env)->GetObjectArrayElement(env,signatures, 0);

    // 获得Signature类
    cls = (*env)->GetObjectClass(env,signature);
    // 得到toCharsString方法的ID
    mid = (*env)->GetMethodID(env,cls, "toByteArray", "()[B");
    // 返回当前应用签名信息
    jbyteArray signatureByteArray = (jbyteArray) (*env)->CallObjectMethod(env,signature, mid);
    return ByteArrayToString(env,signatureByteArray);
}