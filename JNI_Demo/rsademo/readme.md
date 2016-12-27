
#add_library(crypto STATIC IMPORTED)
#set_target_properties(crypto PROPERTIES
#     IMPORTED_LOCATION_RELEASE  src/main/cpp/openssllib/libcrypto.a
#     #IMPORTED_LOCATION_DEBUG   ${CMAKE_CURRENT_SOURCE_DIR}/libbard.a
#
#     ) # <-- dependency is here


#add_library(ssl STATIC IMPORTED)
#set_target_properties(ssl PROPERTIES
#     IMPORTED_LOCATION_RELEASE  src/main/cpp/openslib/libssl.a
#    # IMPORTED_LOCATION_DEBUG   ${CMAKE_CURRENT_SOURCE_DIR}/libbazd.a
#    # IMPORTED_LINK_INTERFACE_LIBRARIES crypto
#    )





add_library(
             native-lib


             SHARED

             src/main/cpp/native-lib.cpp
             src/main/cpp/MyRSA.cpp

             )
FIND_LIBRARY(SLibrarys libssl.a)

#find_library(libssl  app/src/main/cpp/openssllib/)

target_link_libraries(  ${SLibrarys}
                          native-lib
                      )
