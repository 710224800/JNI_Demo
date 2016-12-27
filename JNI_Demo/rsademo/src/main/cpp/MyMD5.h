//
// Created by gzbd on 2016/12/7.
//

#ifndef RSADEMO_MYMD5_H
#define RSADEMO_MYMD5_H

#include <stdio.h>
#include <string>

class MyMD5 {

public:
    static std::string encryptMD5(const std::string& msg);

};


#endif //RSADEMO_MYMD5_H
