#include <jni.h>
#include <string>
#include "./core/rsa_util.h"
#include "./core/base64.h"
using namespace std;
using namespace rsa_util;
using namespace base64;

//测试用公钥
//    -----BEGIN PUBLIC KEY-----
//    MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDw2nJf7UeIRXYWffj4wFaPemEV
//    u0VNWgW/K+Tab+ViwN5WkDJ+230/4SZqmov8hiM5t1wJzNEjtvZhs7Lbegb8z7vX
//    3HlJV48v7/TEL3PpRi+TzPMym+uKtZXPm4ZQZkDlWFg+lc0ksjNeEfDQ2/OKNZ9S
//    7RLBZF6z5fbLhMzPpwIDAQAB
//    -----END PUBLIC KEY-----

//测试用私钥
//    -----BEGIN PRIVATE KEY-----
//    MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAPDacl/tR4hFdhZ9
//    +PjAVo96YRW7RU1aBb8r5Npv5WLA3laQMn7bfT/hJmqai/yGIzm3XAnM0SO29mGz
//    stt6BvzPu9fceUlXjy/v9MQvc+lGL5PM8zKb64q1lc+bhlBmQOVYWD6VzSSyM14R
//    8NDb84o1n1LtEsFkXrPl9suEzM+nAgMBAAECgYEA4pvVMtYQEHGyOlVJ09k7WAE/
//    qO+qs614bLbCupa/DtwCFRXUvLCMNncC6xf/j5cxO1N+QCY5u82gIKqvJHq6aH0+
//    /42iR1ZkbjD4iXKYnZHA4lyRwBAjxt9xenOwptNMu3nj7qKSW5E/zu+3oSWgiiFr
//    o27P5mLghDlRKmqcTwkCQQD9Gmh08BL/gy90W2Qvjcm3ctj+cIvT6gZNGnHtTVOd
//    zFfUhu5cJvUw+tPdD6hZdqBV38KlwZ0OLWsR7XOf9TTbAkEA85wljhCUY+4bY3ZK
//    hrr3H0+mmBsHqIQEwg7oEL84GEpxVJLILdqnkxNuUCMwHmhWrbu7bgjeJO6/ltrd
//    pJZEJQJAC4M4/yCwbIjmDq/dhcA4Tazeq+wooBIECVvLlNSwmfvifttIWk63VmwC
//    WQrOSIt5zY4pB2sgHrX4Kc+YM81ugwJBAIj4EmV+DPDiv6N8rwpxtOB1+EUtbXDi
//    SYqStwgze2as9GuI2+RsPCwFkNCd+EAgihvEoe2MLtq1IiO/iz8u/cECQCyGrkX2
//    pSx7qTTdw2VgNuGSkfBOXHyLQv12NVdZJICo+JYsbQp5G2YXCElOCHIo4YQ6+mxU
//    XFLs/K3VOJqBtNk=
//    -----END PRIVATE KEY-----

//根据RSA公钥加密明文
string encryptByRsaPublicKey(string publicKey,string clearText) {
    string formatPublicKey = format_public_key(publicKey);
    string result = public_key_encrypt(formatPublicKey,clearText);
    result = base64_encode((const char *)result.c_str(),result.length());
    return result;
}

//根据RSA私钥解密密文
string decryptByRsaPrivateKey(string privateKey,string cipherText){
    string formatPrivateKey = format_private_key(privateKey);
    string result = base64_decode(cipherText);
    result = private_key_decrypt(formatPrivateKey,result);
    return result;
}

//从jstring中获取std::string
string getStringFromJString(JNIEnv *env, jstring str){
    const char *cstr = env->GetStringUTFChars(str, NULL);
    std::string strResult = std::string(cstr);
    env->ReleaseStringUTFChars(str, cstr);
    return strResult;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lazyee_module_rsa_RSAUtil_encryptByRSAPublicKey(JNIEnv *env, jclass clazz,
                                                         jstring clear_text) {

    string RSA_PUBLIC_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDw2nJf7UeIRXYWffj4wFaPemEVu0VNWgW/K+Tab+ViwN5WkDJ+230/4SZqmov8hiM5t1wJzNEjtvZhs7Lbegb8z7vX3HlJV48v7/TEL3PpRi+TzPMym+uKtZXPm4ZQZkDlWFg+lc0ksjNeEfDQ2/OKNZ9S7RLBZF6z5fbLhMzPpwIDAQAB";
    string clearText = getStringFromJString(env,clear_text);
    return env->NewStringUTF(encryptByRsaPublicKey(RSA_PUBLIC_KEY,clearText).c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_lazyee_module_rsa_RSAUtil_decryptByRSAPrivateKey(JNIEnv *env, jclass clazz,
                                                          jstring cipher_text) {

    string RSA_PRIVATE_KEY = "MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAPDacl/tR4hFdhZ9+PjAVo96YRW7RU1aBb8r5Npv5WLA3laQMn7bfT/hJmqai/yGIzm3XAnM0SO29mGzstt6BvzPu9fceUlXjy/v9MQvc+lGL5PM8zKb64q1lc+bhlBmQOVYWD6VzSSyM14R8NDb84o1n1LtEsFkXrPl9suEzM+nAgMBAAECgYEA4pvVMtYQEHGyOlVJ09k7WAE/qO+qs614bLbCupa/DtwCFRXUvLCMNncC6xf/j5cxO1N+QCY5u82gIKqvJHq6aH0+/42iR1ZkbjD4iXKYnZHA4lyRwBAjxt9xenOwptNMu3nj7qKSW5E/zu+3oSWgiiFro27P5mLghDlRKmqcTwkCQQD9Gmh08BL/gy90W2Qvjcm3ctj+cIvT6gZNGnHtTVOdzFfUhu5cJvUw+tPdD6hZdqBV38KlwZ0OLWsR7XOf9TTbAkEA85wljhCUY+4bY3ZKhrr3H0+mmBsHqIQEwg7oEL84GEpxVJLILdqnkxNuUCMwHmhWrbu7bgjeJO6/ltrdpJZEJQJAC4M4/yCwbIjmDq/dhcA4Tazeq+wooBIECVvLlNSwmfvifttIWk63VmwCWQrOSIt5zY4pB2sgHrX4Kc+YM81ugwJBAIj4EmV+DPDiv6N8rwpxtOB1+EUtbXDiSYqStwgze2as9GuI2+RsPCwFkNCd+EAgihvEoe2MLtq1IiO/iz8u/cECQCyGrkX2pSx7qTTdw2VgNuGSkfBOXHyLQv12NVdZJICo+JYsbQp5G2YXCElOCHIo4YQ6+mxUXFLs/K3VOJqBtNk=";
    string cipherText = getStringFromJString(env,cipher_text);
    return env->NewStringUTF(decryptByRsaPrivateKey(RSA_PRIVATE_KEY,cipherText).c_str());
}