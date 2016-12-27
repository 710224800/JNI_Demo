
cmake_minimum_required(VERSION 3.4.1)


include_directories(
    src/main/cpp/openssllib/include/openssl/
    )

link_directories(
    src/main/cpp/openssllib/
    )


add_library(
    native

    SHARED

    src/main/cpp/MyRSA.cpp
    src/main/cpp/MyBASE64.cpp
    src/main/cpp/My3DES.cpp
    src/main/cpp/MyMD5.cpp
    src/main/cpp/MyAES.cpp
    src/main/cpp/native-lib.cpp
    )

find_library(
    log-lib
    log
    android
    )

target_link_libraries(
    native
    libcrypto.a
    libssl.a
    android
    ${log-lib}
    ) # 链接动态库




