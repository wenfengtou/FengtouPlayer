package com.wenfengtou.fengtouplayer;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;

import com.wenfengtou.fengtouplayer.view.MyVideoView;

public class FFmpegDrawActivity extends Activity {
    MyVideoView myVideoView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_draw);
        myVideoView = (MyVideoView) findViewById(R.id.myVV);
    }

    @Override
    protected void onResume() {
        super.onResume();
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                //http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
                myVideoView.startPlay("/sdcard/test.mp4");
            }
        },1000);


    }
}
