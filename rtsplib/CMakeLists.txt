cmake_minimum_required(VERSION 3.4.1)


include_directories(src/main/cpp/include/)

add_library( # Sets the name of the library
             rtsplib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s)
             src/main/cpp/rtsp-client.c)

target_link_libraries( # Specifies the target library.
                        rtsplib
                       # Links the target library to the log library
                       # included in the NDK.
                        android
                        log )