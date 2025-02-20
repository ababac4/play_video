#ifndef CMYRSA_H
#define CMYRSA_H

#include <iostream>
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>

using  Rsa_PrivateKey = CryptoPP::RSA::PrivateKey;
using  Rsa_PublicKey =  CryptoPP::RSA::PublicKey;


struct RsaKey{
    CryptoPP::RSA::PrivateKey private_key;
    CryptoPP::RSA::PublicKey public_key;
};


class CMyRsa {
public:
    //生成 公钥私钥, 默认生成密钥位数 2048
    static RsaKey generateKeys(unsigned int key_size = 2048);

    // RSA OAEP 填充模式 使用公钥加密数据
    static std::string RSA_OAEP_Encrypt_Public(const std::string& plainText
                               , CryptoPP::RSA::PublicKey  rsa);

    // RSA OAEP 填充模式 使用私钥解密数据
    static std::string RSA_OAEP_Decrypt_Private(const std::string& cipherText ,
                               CryptoPP::RSA::PrivateKey rsa);

    // 将公钥进行Base64编码并保存到字符串中
    static std::string RSA_EncodePublicKey(const CryptoPP::RSA::PublicKey& publicKey) ;

    // 将Base64编码后的公钥解码为公钥对象
    static CryptoPP::RSA::PublicKey RSA_DecodePublicKey(const std::string& publicKeyStr);

    // 将私钥进行Base64编码并保存到字符串中
    static std::string RSA_EncodePrivateKey(const CryptoPP::RSA::PrivateKey& PrivateKey) ;

    // 将Base64编码后的私钥解码为私钥对象
    static CryptoPP::RSA::PrivateKey RSA_DecodePrivateKey(const std::string& PrivateKeyStr);

};

#endif // CMYRSA_H
