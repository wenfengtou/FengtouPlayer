package com.wenfengtou.fengtouplayer;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.wenfengtou.opengllib.FengtouSurfaceView;
//import com.wenfengtou.rtsplib.RtspClient;

public class OpenglActivity extends AppCompatActivity {

    FengtouSurfaceView mFengtouSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_opengl);
        mFengtouSurfaceView = new FengtouSurfaceView(this);
        setContentView(mFengtouSurfaceView);
       // RtspClient rtspClient = new RtspClient("rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov");
      //  rtspClient.start();
    }
}
