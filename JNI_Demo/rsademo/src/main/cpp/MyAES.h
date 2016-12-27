//
// Created by gzbd on 2016/12/7.
//

#ifndef RSADEMO_MYAES_H
#define RSADEMO_MYAES_H


#include <string>

class MyAES {


public:
    static  std::string encodeAES( const std::string& password, const std::string& data );

   static std::string decodeAES( const std::string& strPassword, const std::string& strData );

};


#endif //RSADEMO_MYAES_H
