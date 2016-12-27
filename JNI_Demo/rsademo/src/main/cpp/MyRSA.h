//
// Created by gzbd on 2016/12/6.
//

#ifndef MYAPPLICATION_MYRSA_H
#define MYAPPLICATION_MYRSA_H

#include <string>





class MyRSA {

public:

    static std::string encryptRSA(const std::string& data,int *lenreturn);
    static std::string decryptRSA(const std::string& data);


};



#endif //MYAPPLICATION_MYRSA_H
