package com.wenfengtou.fengtouplayer;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.wenfengtou.fengtouplayer.view.MyVideoView;

public class FFmpegDrawActivity extends Activity {
    MyVideoView mVideoView;
    ImageView mImageView;
    Bitmap mBitmap;
    LinearLayout mLayout;
    Handler mhandler = new Handler();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_draw);
        mLayout = (LinearLayout) findViewById(R.id.mLayout);
        mVideoView = (MyVideoView) findViewById(R.id.myVV);
        for (int i = 0 ;i < 100;i++) {
            mhandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mImageView = new ImageView(FFmpegDrawActivity.this);
                    mBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a);
                    mImageView.setImageBitmap(mBitmap);
                    mLayout.addView(mImageView);
                }
            },100);

        }

    }


    @Override
    protected void onResume() {
        super.onResume();
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                //"http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"
                mVideoView.startPlay("rtsp://192.168.9.31:6789/1");
            }
        },1000);


    }
}
