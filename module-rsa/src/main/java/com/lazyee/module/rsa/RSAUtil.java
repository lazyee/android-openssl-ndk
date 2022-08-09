package com.lazyee.module.rsa;

/**
 * Author: leeorz
 * Email: 378229364@qq.com
 * Description:
 * Date: 2022/8/9 09:44
 */
public class RSAUtil {
    static {
        System.loadLibrary("rsa");
    }

    public static native String encryptByRSAPublicKey(String clearText);
    public static native String decryptByRSAPrivateKey(String cipherText);
}
