package lzj.com.jnitest;

/**
 * Created by Mark on 2017/7/5.
 */

public class CheckSignatureHelper {
   /* String getSignature() throws Exception{
        Application application = ActivityThread.currentApplication();
        PackageManager manager = application.getPackageManager();
        String packageName = application.getPackageName();
        PackageInfo packageInfo = manager.getPackageInfo(packageName,PackageManager.GET_SIGNATURES);
        Signature signature = packageInfo.signatures[0];
        byte[] chars = signature.toByteArray();
        MessageDigest digest = MessageDigest.getInstance("md5");
        digest.update(chars);
        byte[] objArraySign = digest.digest(chars);

        jsize intArrayLength = env->GetArrayLength(objArraySign);
        jbyte *byte_array_elements = env->GetByteArrayElements(objArraySign, NULL);
        size_t length = (size_t) intArrayLength * 2 + 1;
    char *char_result = (char *) malloc(length);
        memset(char_result, 0, length);

        // 将byte数组转换成16进制字符串，发现这里不用强转，jbyte和unsigned char应该字节数是一样的
        ByteToHexStr((const char *) byte_array_elements, char_result, intArrayLength);
        // 在末尾补\0
    *(char_result + intArrayLength * 2) = '\0';

        jstring stringResult = env->NewStringUTF(char_result);
    }
         */
}
