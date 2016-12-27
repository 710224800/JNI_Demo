//
// Created by gzbd on 2016/12/7.
//




#ifndef RSADEMO_MYBASE64_H
#define RSADEMO_MYBASE64_H


#include <stdio.h>
#include <string>

class MyBASE64 {


public:
    static std::string base64_decode(const std::string& encoded_bytes,
                                      int *decoded_length) ;


    static std::string base64_encode(const std::string& decoded_bytes,
                                       size_t decoded_length) ;



    static std::string base64_encodestring(const std::string &text );
    static  std::string base64_decodestring(const std::string &text );


};


#endif //RSADEMO_MYBASE64_H
