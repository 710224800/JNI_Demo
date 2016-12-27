//
// Created by gzbd on 2016/12/6.
//

#include "MyRSA.h"
#include <string>
#include <cstddef>
#include <stdlib.h>
#include "Log.h"
#include <stdio.h>


#include "openssllib/include/openssl/bio.h"
#include "openssllib/include/openssl/buffer.h"
#include "openssllib/include/openssl/evp.h"
#include "openssllib/include/openssl/rsa.h"
#include "openssllib/include/openssl/pem.h"
#include "openssllib/include/openssl/safestack.h"

#define  PUBLIC_EXPONENT   RSA_F4
#define   MODULUS "9c847aae8aa567d36af169dbed35f42f9568d137067b30a204476897020e7d88914d1c03a671c62be4a05fbd645bd358b2ff38ad2e5166003414eb7b155301d1f6cacaa54260681073e1c02947379614e6b6123e5b35af50dc675f1c673565979cc4acb967976e209bad50d24ab38b6822198644de43874e4fb92714f6fd677d"


#define PUBLICKEY "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCwgKPvbsEqNbBKEuYqQMkCA792\nPddSfNdi5ANcxGneQ38tfeVl3hNGPVpsYMTQYqWeEv+NBufKBadpfBm6HZuOm5nu\nLfSZPPjrM60XBPU5tvg7LJEsS0Uh3hv1pKk8TJVdcfyak56CyMNXXu2r7lXL80GR\n7aXgB+lfj3zfpJIMlQIDAQAB\n-----END PUBLIC KEY-----\n"

#define PRIVATE_KEY  "-----BEGIN RSA PRIVATE KEY-----\nMIICXAIBAAKBgQCwgKPvbsEqNbBKEuYqQMkCA792PddSfNdi5ANcxGneQ38tfeVl\n3hNGPVpsYMTQYqWeEv+NBufKBadpfBm6HZuOm5nuLfSZPPjrM60XBPU5tvg7LJEs\nS0Uh3hv1pKk8TJVdcfyak56CyMNXXu2r7lXL80GR7aXgB+lfj3zfpJIMlQIDAQAB\nAoGBAJ62zrObcG+4X5H8dKRCJX5+SEjXSyyNvlDaoHtm05xeLZqGvyVfEQ30Vb9n\nNRP94NfIVaxHLV9oviYIxkmqHhocAT2Yo1NQpWohljsrmiPHtYqfsgW+w+zSylXe\n+FHrLK+oUOxhDo0hFhhdGRuCnK8GD97Y4EtLg1CsfCIEYQsBAkEA3hABuD9jS2Gs\n/2P1bEHhefxsBUn9I/LaIBwtodA6s7rmGvkdagDT8PByfZnyQ1VeOQ3xC4lL48Tl\nXOxQ2mT35QJBAMt6I6wkieeLWIQKLMLiOkqZw47sP+IbD6zwiioXJ/uW8sHJT6no\nRLrKvQplvdJxuuqz6USr+1IJ1tRiK6PrFvECQD0HEyHqscQ2vM+XTgyJcokO2TT+\n54XoqQ+oDtZonqlkVPbWvcGzJowR2LUyCMV+gZ2WekdcXTHkm9BU1cefdg0CQDwd\nT6CyAtQXhQUthF/nOlWD7BSzk4QXfqAXSJp60OMxi3LZKOIHrxaIgyUpPdWIqDJj\nCM2zCcMJCSEiB8ab0+ECQG682Gh3+xWjXsWsC+UGfyTl2suYwFlpkrl8sk3i/giE\nKoawU1mQhj+BmArC5oixIWQtjxd1rP+8KQ2JB4A0xno=\n-----END RSA PRIVATE KEY-----\n"





std::string MyRSA::decryptRSA(const std::string& data) {


    int ret, flen;
    BIO *bio = NULL;
    RSA *r = NULL;

    if ((bio = BIO_new_mem_buf((void *)PRIVATE_KEY, -1)) == NULL)       //从字符串读取RSA公钥
    {
        LOGE("BIO_new_mem_buf failed!\n");
    }

    r = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);


    flen = RSA_size(r);


    static std::string gkbn;
    gkbn.clear();



    const char *gkbnP=gkbn.c_str();


    const char *dataP=data.c_str();


    ret =RSA_private_decrypt(flen ,(const unsigned char *)dataP, ( unsigned char *)gkbnP, r,
                             RSA_PKCS1_PADDING);//RSA_NO_PADDING //RSA_PKCS1_PADDING

    RSA_free(r);

    CRYPTO_cleanup_all_ex_data(); //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏


    return  gkbn;
}



std::string MyRSA::encryptRSA(const std::string& data, int *lenreturn) {


    int ret, flen;
   BIO *bio = NULL;
   RSA *r = NULL;

    if ((bio = BIO_new_mem_buf((void *)PUBLICKEY, -1)) == NULL)       //从字符串读取RSA公钥
    {
        LOGE("BIO_new_mem_buf failed!\n");
   }

   r = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);

    flen = RSA_size(r);
    lenreturn=&flen;


  static std::string gkbn;
    gkbn.clear();

    unsigned char *src = NULL;
    unsigned char *dst = NULL;


    src = (unsigned char *) malloc(flen+1);//填充0 到 128 长度
    dst = (unsigned char *) malloc(flen+1);

    memset(src, 0, flen);
    memcpy(src, data.c_str(), data.size());




  //  RSA_PKCS1_PADDING 最大加密长度 为 128 -11
   //RSA_NO_PADDING 最大加密长度为  128
    ret = RSA_public_encrypt(flen-11,src, dst, r,
                            RSA_PKCS1_PADDING);//RSA_NO_PADDING //RSA_PKCS1_PADDING


    gkbn.assign((char *)dst);

    RSA_free(r);

    free(src);
    free(dst);

    CRYPTO_cleanup_all_ex_data(); //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏

    return  gkbn;

}

