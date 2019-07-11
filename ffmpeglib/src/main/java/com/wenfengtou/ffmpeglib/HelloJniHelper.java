package com.wenfengtou.ffmpeglib;

public class HelloJniHelper {
    static {
        System.loadLibrary("HelloJniHelper");
    }
    public static native String hello();
}
