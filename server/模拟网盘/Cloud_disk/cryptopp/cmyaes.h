#ifndef CMYAES_H
#define CMYAES_H

#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

class CMyAes {
public:
    //AES CBC 加密  PKCS7填充方案
    // PKCS7 如果明文长度不是块大小的整数倍（128位/16字节），则需要进行填充操作，
    // 使得明文长度能够被块大小整除。
    // 在解密时，会先去除填充字节，以还原原始明文
    // 秘钥正常要求 128/192/256 位 , 实现中如果不足补0
    // 偏移量 sIV 要求是128位 也就是 字符串16的长度( 每个是一个字节 , 一个字节8位 )
    // 秘钥 sKey 偏移量 sIV 明文 plainText  返回密文(16进制数的字符串)
    static std::string AES_CBC_Encryption(const std::string& sKey, const std::string& sIV, const char* plainText);
    // 秘钥 sKey 偏移量 sIV 密文 cipherText  返回明文
    static std::string AES_CBC_Decryption(const std::string& sKey, const std::string& sIV, const std::string& cipherText);
};



#endif // CMYAES_H
