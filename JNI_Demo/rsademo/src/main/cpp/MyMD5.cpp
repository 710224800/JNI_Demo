//
// Created by gzbd on 2016/12/7.
//

#include "MyMD5.h"
#include <algorithm>
#include <md5.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

std::string MyMD5::encryptMD5(const std::string& msg){


    std::string md5Result;

    unsigned  char  md[16];
    int  i;
    char  tmp[3]={ '\0' },buf[33]={ '\0' };
    MD5((const unsigned char *) msg.c_str(), msg.length(), md);
    for  (i = 0; i < 16; i++){
        sprintf (tmp, "%2.2x" ,md[i]);
        strcat (buf,tmp);
    }
    printf ( "%s\n" ,buf);
    md5Result.assign(buf);

    transform(md5Result.begin(), md5Result.end(), md5Result.begin(), ::toupper);//转大写


    return  md5Result;


}