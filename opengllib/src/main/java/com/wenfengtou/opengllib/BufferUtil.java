package com.wenfengtou.opengllib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class BufferUtil {
    public static FloatBuffer floatBuffer;

    public static FloatBuffer fBuffer(float[] a) {
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(a.length * 4);
        byteBuffer.order(ByteOrder.nativeOrder());
        floatBuffer = byteBuffer.asFloatBuffer();
        floatBuffer.put(a);
        floatBuffer.position(0);
        return floatBuffer;
    }
}
