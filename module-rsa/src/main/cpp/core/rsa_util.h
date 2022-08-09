#include <iostream>
#ifndef RSA_UTIL_H
#define RSA_UTIL_H

namespace rsa_util {
    std::string format_public_key(std::string publicKey);
    std::string format_private_key(std::string privateKey);
    std::string public_key_encrypt(const std::string &rsaPublicKey,std::string &clearText);
    std::string private_key_decrypt(const std::string &rsaPrivateKey,const std::string &cipherText);
}

#endif // !RSA_UTIL_H