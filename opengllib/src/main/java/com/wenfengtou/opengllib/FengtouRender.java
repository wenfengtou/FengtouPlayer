package com.wenfengtou.opengllib;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class FengtouRender implements Renderer {

    private static final String TAG = "FengtouRender";
    float[] triangleCoords = {
            0.5f,0.5f,0.0f,//top
            -0.5f,-0.5f,0.0f, //bottom left
            0.5f,-0.5f,0.0f //bottom right
    };

    float[] color = {1.0f,1.0f,1.0f,1.0f};
    FloatBuffer vertextBuffer;

    private final String vertextSharderCode =
    "attribute vec4 vPosition:" +
            "void main {" +
            "gl_Position = vPosition;" +
      "}";

    private final String fragmenttSharderCode =
            "precision medium float:" +
                    "uniform vec4 vColor;" +
                    "void main {" +
                    "gl_FragColor = vColor;" +
                    "}";

    int mProgram;
    int mPositionHandle;
    int mColorHandle;
    static int COORDS_PER_VERTEXT = 3;

    int vertextCount = triangleCoords.length / COORDS_PER_VERTEXT;
    int vertextStride = COORDS_PER_VERTEXT * 4;

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        Log.i(TAG, "onSurfaceCreated");
        GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        /*
        vertextBuffer = BufferUtil.fBuffer(triangleCoords);
        int vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertextSharderCode);
        int fragmentShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmenttSharderCode );
        mProgram = GLES20.glCreateProgram();
        GLES20.glAttachShader(mProgram, vertexShader);
        GLES20.glAttachShader(mProgram, fragmentShader);
        GLES20.glLinkProgram(mProgram);
        */
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        Log.i(TAG, "onSurfaceChanged");
        GLES20.glViewport(0,0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
         Log.i(TAG, "onDrawFrame");
         /*
         GLES20.glUseProgram(mProgram);
         mPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition");
         GLES20.glEnableVertexAttribArray(mPositionHandle);
         GLES20.glVertexAttribPointer(mPositionHandle,COORDS_PER_VERTEXT,GLES20.GL_FLOAT, false,vertextStride,vertextBuffer);
         GLES20.glUniform4fv(mColorHandle,1,color,0);
         GLES20.glDrawArrays(GLES20.GL_TRIANGLES,0,vertextCount);
         GLES20.glDisableVertexAttribArray(mPositionHandle);
         */
    }

    public int loadShader(int type, String shaderCode) {
        int shader = GLES20.glCreateShader(type);
        GLES20.glShaderSource(shader,shaderCode);
        GLES20.glCompileShader(shader);
        return shader;
    }
}
