//
// Created by gzbd on 2016/12/7.
//

#include <des.h>
#include "My3DES.h"
#include "Log.h"



static std::string key;


std::string My3DES::getKey(){



    std::string passwordString="abcdefFGNJghijklmn132sds133g232opqrstuvwxyz13236516fsfghbbx5165615ABCDEFffgfGHIJKLM14986321fsshh4892NOPQRSTUVydfewqWXYZ012345hhj6789";


    srand((unsigned)time(0));  //不加这句每次产生的随机数不变

    int random= arc4random() % passwordString.length();


    std::string key= passwordString.substr(random%(passwordString.length()-24),24);
    return  key;

}




/*
    * 有自定义密码的3DES 加密
   */
 std::string  My3DES::encryptDES(const std::string& data , std::string k, int *lenreturn){

    int docontinue = 1;
    //  char *data = "gubojun"; /* 明文 */
    int data_len;
    int data_rest;
    unsigned char ch;
    unsigned char *src = NULL; /* 补齐后的明文 */
    unsigned char *dst = NULL; /* 解密后的明文 */
    int len;
    unsigned char tmp[8];
    unsigned char in[8];
    unsigned char out[8];

    //	char *k = "12345678"; /* 原始密钥 */

    int key_len;
#define LEN_OF_KEY 24
    //	unsigned char key[LEN_OF_KEY]; /* 补齐后的密钥 */

    unsigned char block_key[9];
    DES_key_schedule ks, ks2, ks3;
    /* 构造补齐后的密钥 */
    key_len = k.length();
  //  memcpy((void *) k.c_str(), k.c_str(), key_len);
  //  memset((void *)(k.c_str() + key_len), 0x00, LEN_OF_KEY - key_len);



    for (int i = 0; i <LEN_OF_KEY - key_len ; i++) {

        k+="0";
    }



    /* 分析补齐明文所需空间及补齐填充数据 */




    data_len = strlen(data.c_str());
    data_rest = data_len % 8;
    len = data_len + (8 - data_rest);
    ch = 8 - data_rest;
    src = (unsigned char *) malloc(len);
    dst = (unsigned char *) malloc(len);
    if (NULL == src || NULL == dst) {
        docontinue = 0;
    }

    if (docontinue) {
        int count;
        int i;
        /* 构造补齐后的加密内容 */
        memset(src, 0, len);
        memcpy(src, data.c_str(), data_len);
        memset(src + data_len, ch, 8 - data_rest);
        /* 密钥置换 */
        memset(block_key, 0, sizeof(block_key));
        memcpy(block_key, k.c_str() + 0, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks);
        memcpy(block_key, k.c_str() + 8, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks2);
        memcpy(block_key, k.c_str() + 16, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks3);
        /* 循环加密/解密，每8字节一次 */
        count = len / 8;
        for (i = 0; i < count; i++) {
            memset(tmp, 0, 8);
            memset(in, 0, 8);
            memset(out, 0, 8);
            memcpy(tmp, src + 8 * i, 8);
            /* 加密 */
            //
            //			DES_ecb_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in,
            //					&schedule, DES_ENCRYPT);
            DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in, &ks,
                             &ks2, &ks3,
                             DES_ENCRYPT);

            /* 解密 */
            //          DES_ecb3_encrypt((const_DES_cblock*) in, (DES_cblock*) out, &ks,
            //                  &ks2, &ks3, DES_DECRYPT);
            /* 将解密的内容拷贝到解密后的明文 */
            //          memcpy(dst + 8 * i, out, 8);
            memcpy(dst + 8 * i, in, 8);
        }
    }

    *lenreturn = len;

    if (NULL != src) {
        free(src);
        src = NULL;
    }

    if (NULL != dst) {

       static std::string eresult;
        eresult.clear();

        eresult.assign(
                (char *) dst);
       free(dst);
        return eresult;

    }


    return NULL;


}
 std::string    My3DES::decryptDES(const std::string& data,  std::string  k, int data_len){

    int docontinue = 1;
    //  char *data = "gubojun"; /* 明文 */
    //  int data_len;
    int data_rest;
    unsigned char ch;
    unsigned char *src = NULL; /* 补齐后的明文 */
    unsigned char *dst = NULL; /* 解密后的明文 */



    int len;
    unsigned char tmp[8];
    unsigned char in[8];
    unsigned char out[8];
    //char *k = "12345678"; /* 原始密钥 */
    	int key_len;
    #define LEN_OF_KEY 24
    //	unsigned char key[LEN_OF_KEY]; /* 补齐后的密钥 */
    unsigned char block_key[9];
    DES_key_schedule ks, ks2, ks3;
    /* 构造补齐后的密钥 */


     key_len = k.length();


     for (int i = 0; i <LEN_OF_KEY - key_len ; i++) {

         k+="0";
     }






     /* 分析补齐明文所需空间及补齐填充数据 */
    data_rest = data_len % 8;
    len = data_len;
    src = (unsigned char *) malloc(len);
    dst = (unsigned char *) malloc(len);
    if (NULL == src || NULL == dst) {
        docontinue = 0;
    }
    if (docontinue) {
        int count;
        int i;
        /* 构造补齐后的加密内容 */
        memset(src, 0, len);
        memcpy(src, data.c_str(), data_len);
        /* 密钥置换 */
        memset(block_key, 0, sizeof(block_key));
        memcpy(block_key, k.c_str() + 0, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks);
        memcpy(block_key, k.c_str() + 8, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks2);
        memcpy(block_key, k.c_str() + 16, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks3);

        /* 循环加密/解密，每8字节一次 */
        count = len / 8;
        for (i = 0; i < count; i++) {
            memset(tmp, 0, 8);
            memset(out, 0, 8);
            memcpy(tmp, src + 8 * i, 8);
            /* 加密 */
            //          DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in, &ks,
            //                  &ks2, &ks3, DES_ENCRYPT);
            /* 解密 */
            DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) out, &ks,
                             &ks2, &ks3,
                             DES_DECRYPT);
            /* 将解密的内容拷贝到解密后的明文 */
            memcpy((dst + 8 * i), out, 8);


        }
        for (i = 0; i < len; i++) {
            if (*(dst + i) < 9) {
                *(dst + i) = 0;

                break;
            }
        }
    }

    if (NULL != src) {
        free(src);
        src = NULL;
    }
    if (NULL != dst) {


        static std::string dresult;

        dresult.clear();

        dresult.assign((char *)dst);
        free(dst);
        return dresult;
    }

    return NULL;

}
/*
 * 自动生成密码的加解密，密码加解密一次后会自动生成新的，以前的数据解密会失败
 */
  std::string   My3DES::encryptDES(const std::string& data , int *lenreturn){


     key=getKey();


    int docontinue = 1;
    //  char *data = "gubojun"; /* 明文 */
    int data_len;
    int data_rest;
    unsigned char ch;
    unsigned char *src = NULL; /* 补齐后的明文 */
    unsigned char *dst = NULL; /* 解密后的明文 */
    int len;
    unsigned char tmp[8];
    unsigned char in[8];
    unsigned char out[8];

    //	char *k = "12345678"; /* 原始密钥 */

    int key_len;
#define LEN_OF_KEY 24
    //	unsigned char key[LEN_OF_KEY]; /* 补齐后的密钥 */

    unsigned char block_key[9];
    DES_key_schedule ks, ks2, ks3;
    /* 构造补齐后的密钥 */




    key_len = key.length();


    for (int i = 0; i <LEN_OF_KEY - key_len ; i++) {

        key+="0";
    }




    /* 分析补齐明文所需空间及补齐填充数据 */
    data_len = strlen(data.c_str());
    data_rest = data_len % 8;
    len = data_len + (8 - data_rest);
    ch = 8 - data_rest;
    src = (unsigned char *) malloc(len);
    dst = (unsigned char *) malloc(len);
    if (NULL == src || NULL == dst) {
        docontinue = 0;
    }

    if (docontinue) {
        int count;
        int i;
        /* 构造补齐后的加密内容 */
        memset(src, 0, len);
        memcpy(src, data.c_str(), data_len);
        memset(src + data_len, ch, 8 - data_rest);
        /* 密钥置换 */
        memset(block_key, 0, sizeof(block_key));
        memcpy(block_key, key.c_str() + 0, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks);
        memcpy(block_key, key.c_str() + 8, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks2);
        memcpy(block_key, key.c_str() + 16, 8);
        DES_set_key_unchecked((const_DES_cblock*) block_key, &ks3);
        /* 循环加密/解密，每8字节一次 */
        count = len / 8;
        for (i = 0; i < count; i++) {
            memset(tmp, 0, 8);
            memset(in, 0, 8);
            memset(out, 0, 8);
            memcpy(tmp, src + 8 * i, 8);
            /* 加密 */
            //
            //			DES_ecb_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in,
            //					&schedule, DES_ENCRYPT);
            DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in, &ks,
                             &ks2, &ks3,
                             DES_ENCRYPT);

            /* 解密 */
            //          DES_ecb3_encrypt((const_DES_cblock*) in, (DES_cblock*) out, &ks,
            //                  &ks2, &ks3, DES_DECRYPT);
            /* 将解密的内容拷贝到解密后的明文 */
            //          memcpy(dst + 8 * i, out, 8);
            memcpy(dst + 8 * i, in, 8);
        }
    }

    *lenreturn = len;
    if (NULL != src) {
        free(src);
        src = NULL;
    }

    if (NULL != dst) {

        static std::string result;
        result.clear();

        result.assign(
                (char *) dst);
        free(dst);
        return result;

    }



    return NULL;



}
  std::string   My3DES::decryptDES(const std::string& data , int data_len){


      int docontinue = 1;
      //  char *data = "gubojun"; /* 明文 */
      //  int data_len;
      int data_rest;
      unsigned char ch;
      unsigned char *src = NULL; /* 补齐后的明文 */
      unsigned char *dst = NULL; /* 解密后的明文 */



      int len;
      unsigned char tmp[8];
      unsigned char in[8];
      unsigned char out[8];
      //char *k = "12345678"; /* 原始密钥 */
      	int key_len;
#define LEN_OF_KEY 24
      //	unsigned char key[LEN_OF_KEY]; /* 补齐后的密钥 */
      unsigned char block_key[9];
      DES_key_schedule ks, ks2, ks3;
      /* 构造补齐后的密钥 */



      key_len = key.length();

      for (int i = 0; i <LEN_OF_KEY - key_len ; i++) {

          key+="0";
      }


      /* 分析补齐明文所需空间及补齐填充数据 */
      data_rest = data_len % 8;
      len = data_len;
      src = (unsigned char *) malloc(len);
      dst = (unsigned char *) malloc(len);
      if (NULL == src || NULL == dst) {
          docontinue = 0;
      }
      if (docontinue) {
          int count;
          int i;
          /* 构造补齐后的加密内容 */
          memset(src, 0, len);
          memcpy(src, data.c_str(), data_len);
          /* 密钥置换 */
          memset(block_key, 0, sizeof(block_key));
          memcpy(block_key, key.c_str() + 0, 8);
          DES_set_key_unchecked((const_DES_cblock*) block_key, &ks);
          memcpy(block_key, key.c_str() + 8, 8);
          DES_set_key_unchecked((const_DES_cblock*) block_key, &ks2);
          memcpy(block_key, key.c_str() + 16, 8);
          DES_set_key_unchecked((const_DES_cblock*) block_key, &ks3);

          /* 循环加密/解密，每8字节一次 */
          count = len / 8;
          for (i = 0; i < count; i++) {
              memset(tmp, 0, 8);
              memset(out, 0, 8);
              memcpy(tmp, src + 8 * i, 8);
              /* 加密 */
              //          DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in, &ks,
              //                  &ks2, &ks3, DES_ENCRYPT);
              /* 解密 */
              DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) out, &ks,
                               &ks2, &ks3,
                               DES_DECRYPT);
              /* 将解密的内容拷贝到解密后的明文 */
              memcpy((dst + 8 * i), out, 8);


          }
          for (i = 0; i < len; i++) {
              if (*(dst + i) < 9) {
                  *(dst + i) = 0;

                  break;
              }
          }
      }

      if (NULL != src) {
          free(src);
          src = NULL;
      }
      if (NULL != dst) {


          static std::string result;
          result.clear();
          result.assign((char *)dst);
          free(dst);
          return result;
      }

      return NULL;



}