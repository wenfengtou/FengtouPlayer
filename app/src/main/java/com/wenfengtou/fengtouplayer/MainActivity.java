package com.wenfengtou.fengtouplayer;

import android.graphics.SurfaceTexture;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import tv.danmaku.ijk.media.player.IMediaPlayer;
import tv.danmaku.ijk.media.player.IjkMediaPlayer;

public class MainActivity extends AppCompatActivity {

    private IjkMediaPlayer player;
    private TextureView ttv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        player = new IjkMediaPlayer();
        //player.setVolume(0, 0);
        ttv = (TextureView) findViewById(R.id.text_screen);
       // ttv.setVisibility(0);
        ttv.setSurfaceTextureListener(new TextureListen());
        try {
            // cctv1 http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
            String stream_url = "http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8";
            player.setDataSource(this, Uri.parse(stream_url));
            player.prepareAsync();
            /*
            player.setOnPreparedListener(new IjkMediaPlayer.() {
                @Override
                public void onPrepared(IjkMediaPlayer mp) {
                    player.start();
                    Log.i("wenfengplayer","player start");
                    player.setLooping(true);
                }
            });
            */
            player.setOnPreparedListener(new IMediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(IMediaPlayer mp) {
                    player.start();
                    Log.i("wenfengplayer","player start");
                    player.setLooping(true);
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }

        Button btn_image = (Button)findViewById(R.id.button);
        btn_image.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ImageView img = (ImageView) findViewById(R.id.image_screen);
                img.setImageBitmap(ttv.getBitmap());
            }
        });

    }
    private class TextureListen implements TextureView.SurfaceTextureListener {

        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int i, int i1) {
            try {
                Log.i("wenfengplayer","onSurfaceTextureAvailable");
                player.setSurface(new Surface(surfaceTexture));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int i, int i1) {

        }

        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
            return false;
        }

        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
        }
    }
}
