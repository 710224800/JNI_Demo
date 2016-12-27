//
// Created by gzbd on 2016/12/7.
//

#include <aes.h>
#include "MyAES.h"

/**
 * 密码长度为 16 位  ,加密长度为  128
 * 密码长度为 24 位  ,加密长度为  192
 * 密码长度为 32 位  ,加密长度为  256
 *
 *
 */
std::string MyAES::encodeAES( const std::string& password, const std::string& data )
{
    AES_KEY aes_key;
    if(AES_set_encrypt_key((const unsigned char*)password.c_str(), password.length() * 8, &aes_key) < 0)
    {
        return "null";
    }
    std::string strRet;
    std::string data_bak = data;
    unsigned int data_length = data_bak.length();
    int padding = 0;
    if (data_bak.length() % AES_BLOCK_SIZE > 0)
    {
        padding =  AES_BLOCK_SIZE - data_bak.length() % AES_BLOCK_SIZE;
    }
    data_length += padding;
    while (padding > 0)
    {
        data_bak += '\0';
        padding--;
    }
    for(unsigned int i = 0; i < data_length/AES_BLOCK_SIZE; i++)
    {
        std::string str16 = data_bak.substr(i*AES_BLOCK_SIZE, AES_BLOCK_SIZE);
        unsigned char out[AES_BLOCK_SIZE];
        ::memset(out, 0, AES_BLOCK_SIZE);
        AES_encrypt((const unsigned char*)str16.c_str(), out, &aes_key);
        strRet += std::string((const char*)out, AES_BLOCK_SIZE);
    }
    return strRet;
}


std::string MyAES::decodeAES( const std::string& strPassword, const std::string& strData )
{
    AES_KEY aes_key;
    if(AES_set_decrypt_key((const unsigned char*)strPassword.c_str(), strPassword.length() * 8, &aes_key) < 0)
    {
        return "null";
    }
    std::string strRet;
    for(unsigned int i = 0; i < strData.length()/AES_BLOCK_SIZE; i++)
    {
        std::string str16 = strData.substr(i*AES_BLOCK_SIZE, AES_BLOCK_SIZE);
        unsigned char out[AES_BLOCK_SIZE];
        ::memset(out, 0, AES_BLOCK_SIZE);
        AES_decrypt((const unsigned char*)str16.c_str(), out, &aes_key);
        strRet += std::string((const char*)out, AES_BLOCK_SIZE);
    }
    return strRet;
}