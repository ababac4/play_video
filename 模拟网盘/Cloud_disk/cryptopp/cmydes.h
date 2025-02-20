#ifndef CMYDES_H
#define CMYDES_H





#include <iostream>

#include "cryptopp/cryptlib.h"
#include "cryptopp/des.h"
#include "cryptopp/filters.h"
#include "cryptopp/modes.h"

#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"


using namespace std;
using namespace CryptoPP;

class CMyDes
{
public:
    // DES CBC 模式加密  秘钥 sKey   偏移量sIV  明文 plainText 返回密文
    static string DES_CBC_Encryption(string sKey, std::string sIV
                              , const char *plainText) ;
    // DES CBC 模式解密  秘钥 sKey   偏移量sIV  密文 cipherText 返回明文
    static string DES_CBC_Decryption(std::string sKey, std::string sIV,
                              const char *cipherText);
};




#endif // CMYDES_H
