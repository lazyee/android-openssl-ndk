#include "rsa_util.h"
#include "../include/openssl/rsa.h"
#include "../include/openssl/pem.h"
// #include "openssl/rsa.h"
#include "openssl/pem.h"
#include <cmath>

// http://blog.wjsrs.com/post-43.html; 样例代码


std::string rsa_util::format_public_key(std::string publicKey){
    int blockLen = 64;
    int loopCount = ceil(publicKey.size() / (blockLen * 1.0));

    std::string formatRsaPublicKey = "-----BEGIN PUBLIC KEY-----\n";
    for(int i = 0;i<loopCount;i++){
        formatRsaPublicKey.append(publicKey.substr(i * blockLen ,blockLen));
        formatRsaPublicKey.append("\n");
    }
    formatRsaPublicKey.append("-----END PUBLIC KEY-----\n");
    return formatRsaPublicKey;
}

std::string rsa_util::format_private_key(std::string privateKey){
    int blockLen = 64;
    int loopCount = ceil(privateKey.size() / (blockLen * 1.0));

    std::string formatRsaPrivateKey = "-----BEGIN PRIVATE KEY-----\n";
    for(int i = 0;i<loopCount;i++){
        formatRsaPrivateKey.append(privateKey.substr(i * blockLen ,blockLen));
        formatRsaPrivateKey.append("\n");
    }
    formatRsaPrivateKey.append("-----END PRIVATE KEY-----\n");
    return formatRsaPrivateKey;
}

std::string rsa_util::public_key_encrypt(const std::string &rsaPublicKey,std::string &clearText){
    std::string strRet;
    // 创建RSA指针
    BIO *keybio = BIO_new_mem_buf((unsigned char *)rsaPublicKey.c_str(),-1);

    RSA* rsa = RSA_new();
    rsa = PEM_read_bio_RSA_PUBKEY(keybio,&rsa,NULL,NULL);
    if(!rsa){
        BIO_free_all(keybio);
        return std::string("");
    }

    int len = RSA_size(rsa);
    char *encryptedText = (char *)malloc(len + 1);
    memset(encryptedText,0,len + 1);

    //加密函数
    int ret = RSA_public_encrypt(clearText.length(),(const unsigned char*) clearText.c_str(),(unsigned char*) encryptedText,rsa,RSA_PKCS1_PADDING);
    if(ret > 0)
        strRet = std::string(encryptedText,ret);

    //释放内存
    free(encryptedText);
    BIO_free_all(keybio);
    RSA_free(rsa);

    return strRet;
}

std::string rsa_util::private_key_decrypt(const std::string &rsaPrivateKey,const std::string &cipherText){
    std::string strRet;
    RSA *rsa = RSA_new();
    BIO *keybio;
    keybio = BIO_new_mem_buf((unsigned char *)rsaPrivateKey.c_str(), -1);

    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

    int len = RSA_size(rsa);
    char *decryptedText = (char *)malloc(len + 1);
    memset(decryptedText, 0, len + 1);

    // 解密函数
    int ret = RSA_private_decrypt(cipherText.length(), (const unsigned char*)cipherText.c_str(), (unsigned char*)decryptedText, rsa, RSA_PKCS1_PADDING);
    if (ret >= 0)
        strRet = std::string(decryptedText, ret);

    // 释放内存
    free(decryptedText);
    BIO_free_all(keybio);
    RSA_free(rsa);
    return strRet;
}
