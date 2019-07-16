package com.wenfengtou.fengtouplayer;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.wenfengtou.opengllib.FengtouSurfaceView;

public class OpenglActivity extends AppCompatActivity {

    FengtouSurfaceView mFengtouSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_opengl);
        mFengtouSurfaceView = new FengtouSurfaceView(this);
        setContentView(mFengtouSurfaceView);
    }
}
