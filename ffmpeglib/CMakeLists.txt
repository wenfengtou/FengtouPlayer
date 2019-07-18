cmake_minimum_required(VERSION 3.4.1)


include_directories(src/main/cpp/ffmpeg/)
include_directories(../rtsplib/src/main/cpp/include/)

add_library( # Sets the name of the library
             HelloJniHelper

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s)
             src/main/cpp/hello.cpp
             src/main/cpp/FFmpegNativeUtil.cpp )

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavcodec-58.so)

add_library(avdevice SHARED IMPORTED)
set_target_properties(avdevice PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavdevice-58.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavfilter-7.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavformat-58.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libavutil-56.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libswresample-3.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libswscale-5.so)

add_library(rtsplib SHARED IMPORTED)
set_target_properties(rtsplib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/librtsplib.so)

target_link_libraries( # Specifies the target library.
                        HelloJniHelper
                        rtsplib
                        avcodec
                        avdevice
                        avfilter
                        avformat
                        avutil
                        swresample
                        swscale
                       # Links the target library to the log library
                       # included in the NDK.
                        android
                        log )