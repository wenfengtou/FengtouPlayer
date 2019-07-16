package com.wenfengtou.opengllib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class FengtouSurfaceView extends GLSurfaceView {

    FengtouRender mRender;
    public FengtouSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        mRender = new FengtouRender();
        setRenderer(mRender);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public FengtouSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }
}
