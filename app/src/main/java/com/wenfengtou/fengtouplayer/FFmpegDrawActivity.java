package com.wenfengtou.fengtouplayer;

import android.app.Activity;
import android.os.Bundle;
import com.wenfengtou.fengtouplayer.view.MyVideoView;

public class FFmpegDrawActivity extends Activity {
    MyVideoView myVideoView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_draw);
        myVideoView = (MyVideoView) findViewById(R.id.myVV);
        myVideoView.startPlay("http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8");
    }
}
