#include "cmyaes.h"

std::string CMyAes::AES_CBC_Encryption(const std::string& sKey, const std::string& sIV, const char* plainText) {
    std::string strCipherText;

    // Ensure the key length is 16 bytes (128 bits)
    CryptoPP::SecByteBlock key((const byte*)sKey.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    byte iv[CryptoPP::AES::BLOCKSIZE];
    memcpy(iv, sIV.data(), CryptoPP::AES::BLOCKSIZE);

    try {
        // Create AES encryption object
        CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

        // Create a Hex encoder and a StreamTransformationFilter
        CryptoPP::StreamTransformationFilter cbcEncryptor(
            cbcEncryption,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(strCipherText)),
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING
        );

        // Input plaintext to the filter
        cbcEncryptor.Put((const byte*)plainText, strlen(plainText));
        cbcEncryptor.MessageEnd();
    } catch (const CryptoPP::Exception& e) {
        std::cout << e.what() << std::endl;
    }

    return strCipherText;
}

std::string CMyAes::AES_CBC_Decryption(const std::string& sKey, const std::string& sIV, const std::string& cipherText) {
    std::string strPlainText;

    CryptoPP::SecByteBlock key((const byte*)sKey.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    byte iv[CryptoPP::AES::BLOCKSIZE];
    memcpy(iv, sIV.data(), CryptoPP::AES::BLOCKSIZE);

    try {
        // Create the decryption object
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        // Create a Hex decoder and a StreamTransformationFilter
        CryptoPP::HexDecoder decryptor(new CryptoPP::StreamTransformationFilter(
            cbcDecryption,
            new CryptoPP::StringSink(strPlainText),
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING
        ));

        // Input the hex-encoded ciphertext for decryption
        decryptor.Put((const byte*)cipherText.data(), cipherText.size());
        decryptor.MessageEnd();
    } catch (const CryptoPP::Exception& e) {
        std::cout << e.what() << std::endl;
    }

    return strPlainText;
}
