package com.eggsy.photoshop.activity;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.request.RequestListener;
import com.bumptech.glide.request.target.Target;
import com.eggsy.photoshop.EPhotoShop;
import com.eggsy.photoshop.R;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

    @BindView(R.id.iv_img)
    ImageView mIvImg;

    Bitmap bitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ButterKnife.bind(this);

        initView();
    }

    private void initView(){
        Glide.with(this).load(R.mipmap.timg).asBitmap().listener(new RequestListener<Integer, Bitmap>() {
            @Override
            public boolean onException(Exception e, Integer model, Target<Bitmap> target, boolean isFirstResource) {
                return false;
            }

            @Override
            public boolean onResourceReady(Bitmap resource, Integer model, Target<Bitmap> target, boolean isFromMemoryCache, boolean isFirstResource) {
                bitmap = resource;
                return false;
            }
        }).into(mIvImg);
    }

    @OnClick(R.id.btn_gray)
    public void clickGray(View v){
        EPhotoShop.doGray(bitmap);
        mIvImg.setImageBitmap(bitmap);
    }

    static {
        System.loadLibrary("ephotoshop");
    }
}
