#include "cmydes.h"

//采用 DES-CBC-pkcs7
string CMyDes::DES_CBC_Encryption(string sKey, std::string sIV, const char *plainText) {
  std::string strCipherText;

  try {
    // 填key
    CryptoPP::SecByteBlock key(CryptoPP::DES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= CryptoPP::DES::MAX_KEYLENGTH
        ? memcpy(key, sKey.c_str(), sKey.size())
        : memcpy(key, sKey.c_str(), CryptoPP::DES::MAX_KEYLENGTH);

    // 填iv
    byte iv[CryptoPP::DES::BLOCKSIZE];
    memset(iv, 0x30, CryptoPP::DES::BLOCKSIZE);
    sIV.size() <= CryptoPP::DES::BLOCKSIZE
        ? memcpy(iv, sIV.c_str(), sIV.size())
        : memcpy(iv, sIV.c_str(), CryptoPP::DES::BLOCKSIZE);

    CryptoPP::DES::Encryption desEncryption((byte *)key,
                                            CryptoPP::DES::MAX_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(desEncryption,
                                                                iv);

    CryptoPP::StreamTransformationFilter cbcEncryptor(
        cbcEncryption,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(strCipherText)),
        CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING);

    cbcEncryptor.Put((byte *)plainText, strlen(plainText));
    cbcEncryptor.MessageEnd();
  } catch (const CryptoPP::Exception &e) {
    std::cout << e.what() << std::endl;
  }
  return strCipherText;
}


string CMyDes::DES_CBC_Decryption(std::string sKey, std::string sIV,
                               const char *cipherText) {
  std::string strPlainText;

  try {
    // 填key
    CryptoPP::SecByteBlock key(CryptoPP::DES::MAX_KEYLENGTH);
    memset(key, 0x30, key.size());
    sKey.size() <= CryptoPP::DES::MAX_KEYLENGTH
        ? memcpy(key, sKey.c_str(), sKey.size())
        : memcpy(key, sKey.c_str(), CryptoPP::DES::MAX_KEYLENGTH);

    // 填iv
    byte iv[CryptoPP::DES::BLOCKSIZE];
    memset(iv, 0x30, CryptoPP::DES::BLOCKSIZE);
    sIV.size() <= CryptoPP::DES::BLOCKSIZE
        ? memcpy(iv, sIV.c_str(), sIV.size())
        : memcpy(iv, sIV.c_str(), CryptoPP::DES::BLOCKSIZE);

    CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption cbcDecryption(
        (byte *)key, CryptoPP::DES::MAX_KEYLENGTH, iv);

    CryptoPP::HexDecoder decryptor(new CryptoPP::StreamTransformationFilter(
        cbcDecryption, new CryptoPP::StringSink(strPlainText),
        CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING));

    decryptor.Put((byte *)cipherText, strlen(cipherText));
    decryptor.MessageEnd();
  } catch (const CryptoPP::Exception &e) {
    std::cout << e.what() << std::endl;
  }

  return strPlainText;
}
