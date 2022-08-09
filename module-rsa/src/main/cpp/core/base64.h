#include <iostream>
#ifndef _RSA_UTILS_BASE64
#define _RSA_UTILS_BASE64
namespace base64{
    std::string base64_encode(char const* bytes_to_encode, int in_len);
    std::string base64_decode(std::string & encoded_string);
}

#endif // !_RSA_UTILS_BASE64
