#include "cmyrsa.h"


//生成 公钥私钥, 默认生成密钥位数 2048
RsaKey CMyRsa::generateKeys( unsigned int key_size ) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng,key_size);

    RsaKey keys;
    keys.private_key = params;
    keys.public_key = params;

    return keys;
}


// RSA CBC 模式 使用公钥加密数据
std::string CMyRsa::RSA_OAEP_Encrypt_Public(const std::string& plainText ,
                                       CryptoPP::RSA::PublicKey  rsa)  {
    std::string cipherText;

    try {
        CryptoPP::AutoSeededRandomPool rng;

        CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(rsa);
        CryptoPP::StringSource(plainText, true,
            new CryptoPP::PK_EncryptorFilter(rng, encryptor,
                new CryptoPP::Base64Encoder(new CryptoPP::StringSink(cipherText))));
    }
    catch (const CryptoPP::Exception& e) {
        std::cout << e.what() << std::endl;
    }

    return cipherText;
}

// RSA CBC 模式 使用私钥解密数据
std::string CMyRsa::RSA_OAEP_Decrypt_Private(const std::string& cipherText ,
                                      CryptoPP::RSA::PrivateKey  rsa)  {
    std::string decryptedText;

    try {
        CryptoPP::AutoSeededRandomPool rng;

        CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(rsa);
        CryptoPP::StringSource(cipherText, true,
            new CryptoPP::Base64Decoder(new CryptoPP::PK_DecryptorFilter(rng, decryptor,
                new CryptoPP::StringSink(decryptedText))));
    }
    catch (const CryptoPP::Exception& e) {
        std::cout << e.what() << std::endl;
    }

    return decryptedText;
}



// 将公钥进行Base64编码并保存到字符串中
std::string CMyRsa::RSA_EncodePublicKey(const CryptoPP::RSA::PublicKey& publicKey) {
    std::string result;
    CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(result));
    publicKey.Save(encoder);
    encoder.MessageEnd();
    return result;
}

// 将Base64编码后的公钥解码为公钥对象
CryptoPP::RSA::PublicKey CMyRsa::RSA_DecodePublicKey(const std::string& publicKeyStr) {
    CryptoPP::RSA::PublicKey publicKey;
    std::string decoded;
    CryptoPP::Base64Decoder decoder(new CryptoPP::StringSink(decoded));
    decoder.Put(reinterpret_cast<const unsigned char*>(publicKeyStr.data()), publicKeyStr.size());
    decoder.MessageEnd();
    CryptoPP::StringSource source(decoded, true);
    publicKey.Load(source);
    return publicKey;
}

// 将私钥进行Base64编码并保存到字符串中
std::string CMyRsa::RSA_EncodePrivateKey(const CryptoPP::RSA::PrivateKey &PrivateKey)
{
    std::string result;
    CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(result));
    PrivateKey.Save(encoder);
    encoder.MessageEnd();
    return result;
}

// 将Base64编码后的私钥解码为私钥对象
CryptoPP::RSA::PrivateKey CMyRsa::RSA_DecodePrivateKey(const std::string &PrivateKeyStr)
{
    CryptoPP::RSA::PrivateKey privateKey;
    std::string decoded;
    CryptoPP::Base64Decoder decoder(new CryptoPP::StringSink(decoded));
    decoder.Put(reinterpret_cast<const unsigned char*>(PrivateKeyStr.data()), PrivateKeyStr.size());
    decoder.MessageEnd();
    CryptoPP::StringSource source(decoded, true);
    privateKey.Load(source);
    return privateKey;
}



