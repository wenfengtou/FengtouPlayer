package com.wenfengtou.ffmpeglib;

import android.view.Surface;

public class FFmpegNativeUtil {
    static {
        System.loadLibrary("HelloJniHelper");
    }
    public static native void videoStreamPlay(String path, Surface surface);
}
