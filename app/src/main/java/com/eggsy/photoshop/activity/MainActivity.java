package com.eggsy.photoshop.activity;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.SeekBar;

import com.bumptech.glide.Glide;
import com.bumptech.glide.request.RequestListener;
import com.bumptech.glide.request.target.Target;
import com.eggsy.photoshop.EPhotoShop;
import com.eggsy.photoshop.R;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener {

    @BindView(R.id.iv_img)
    ImageView mIvImg;

    @BindView(R.id.sb_blur_radius)
    SeekBar mSbBlurRadius;

    Bitmap srcBitmap;

    private static final String TAG = MainActivity.class.getSimpleName();

    private static final int MOD_CONTRAST = 1;
    private static final int MOD_BRIGHTNESS = 2;
    private static final int MOD_SATURATION = 3;
    private static final int MOD_BLUR = 4;

    int mod = 0;
    int mContrastValue = 20;
    int mBlurValue = 0;
    int mSaturationValue = 0;
    int mBrightnessValue = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ButterKnife.bind(this);

        initView();
    }

    private void initView() {
        Glide.with(this).load(R.mipmap.timg).asBitmap().listener(new RequestListener<Integer, Bitmap>() {
            @Override
            public boolean onException(Exception e, Integer model, Target<Bitmap> target, boolean isFirstResource) {
                return false;
            }

            @Override
            public boolean onResourceReady(Bitmap resource, Integer model, Target<Bitmap> target, boolean isFromMemoryCache, boolean isFirstResource) {
                srcBitmap = resource;
                return false;
            }
        }).into(mIvImg);

        mSbBlurRadius.setOnSeekBarChangeListener(this);
    }

    @OnClick(R.id.btn_src)
    public void clickSrc(View v) {
        mIvImg.setImageBitmap(srcBitmap);
        hideSeekBar();
    }

    @OnClick(R.id.btn_gray)
    public void clickGray(View v) {
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doGray(newBitMap);
        mIvImg.setImageBitmap(newBitMap);
        hideSeekBar();
    }

    @OnClick(R.id.btn_emboss)
    public void clickEmboss(View v) {
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doEmboss(newBitMap);
        mIvImg.setImageBitmap(newBitMap);
        hideSeekBar();
    }

    @OnClick(R.id.btn_blackwhite)
    public void clickBlackWhite(View v) {
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doBlackWhite(newBitMap);
        mIvImg.setImageBitmap(newBitMap);
        hideSeekBar();
    }

    @OnClick(R.id.btn_photographicPlate)
    public void clickPhotographicPlate(View v) {
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doPhotographicPlate(newBitMap);
        mIvImg.setImageBitmap(newBitMap);
        hideSeekBar();
    }

    @OnClick(R.id.btn_fastblur)
    public void clickFastBlur(View v) {
        mod = MOD_BLUR;
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doFastBlur(newBitMap, mBlurValue);
        mIvImg.setImageBitmap(newBitMap);
        showSeekBar(mBlurValue, 30);
    }

    @OnClick(R.id.btn_contrast)
    public void clickContrast(View v) {
        mod = MOD_CONTRAST;
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doContrast(newBitMap, fixNativeContrast(mContrastValue));
        mIvImg.setImageBitmap(newBitMap);
        showSeekBar(mContrastValue, 100);
    }

    @OnClick(R.id.btn_brightness)
    public void clickBrightness(View v) {
        mod = MOD_BRIGHTNESS;
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doBrightness(newBitMap, fixNativeBrightness(mBrightnessValue));
        mIvImg.setImageBitmap(newBitMap);
        showSeekBar(fixSeekbarBrightness(mBrightnessValue), 511);
    }

    @OnClick(R.id.btn_saturation)
    public void clickSaturation(View v) {
        mod = MOD_SATURATION;
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doSaturation(newBitMap, fixNativeSaturation(mSaturationValue));
        mIvImg.setImageBitmap(newBitMap);
        showSeekBar(mSaturationValue, 100);
    }

    @OnClick(R.id.btn_nostalgic)
    public void clickNostalgic(View v) {
        Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
        EPhotoShop.doNostalgic(newBitMap);
        mIvImg.setImageBitmap(newBitMap);
        hideSeekBar();
    }

    static {
        System.loadLibrary("ephotoshop");
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if (!fromUser) {
            return;
        }
        Log.d(TAG, "process : "+progress);
        switch (mod) {
            case MOD_BLUR:
                mBlurValue = progress;
                Bitmap blurBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
                EPhotoShop.doFastBlur(blurBitMap, progress);
                mIvImg.setImageBitmap(blurBitMap);
                break;
            case MOD_BRIGHTNESS:
                mBrightnessValue = progress;
                Bitmap brightnessBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
                EPhotoShop.doBrightness(brightnessBitMap, fixNativeBrightness(mBrightnessValue));
                mIvImg.setImageBitmap(brightnessBitMap);
                break;
            case MOD_CONTRAST:
                mContrastValue = progress;
                Bitmap contrastBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
                EPhotoShop.doContrast(contrastBitMap, fixNativeContrast(progress));
                mIvImg.setImageBitmap(contrastBitMap);
                break;
            case MOD_SATURATION:
                mSaturationValue = progress;
                Bitmap saturationBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
                EPhotoShop.doSaturation(saturationBitMap, fixNativeSaturation(mSaturationValue));
                mIvImg.setImageBitmap(saturationBitMap);
                break;
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }

    private void showSeekBar(int value, int maxValue) {  // ,float minValue,int maxValue
        Animation animation = AnimationUtils.loadAnimation(this, R.anim.bottom_popup);
        mSbBlurRadius.setAnimation(animation);
        mSbBlurRadius.setVisibility(View.VISIBLE);
        mSbBlurRadius.setMax(maxValue);
        mSbBlurRadius.setProgress(value);
        animation.start();
    }

    private float fixNativeSaturation(int saturationValue){
        return (float)saturationValue/40;
    }

    private int fixSeekbarBrightness(int seekbarBrightnessValue) {
        return seekbarBrightnessValue < 0 ? 256 : seekbarBrightnessValue;
    }

    private int fixNativeBrightness(int seekbarBrightnessValue) {
        return seekbarBrightnessValue < 0 ? 0 : seekbarBrightnessValue - 256;
    }

    private float fixNativeContrast(int seekbarContrastValue) {
        return (float)seekbarContrastValue/20;
    }

    private void hideSeekBar() {
        if (mSbBlurRadius.getVisibility() == View.VISIBLE) {
            mSbBlurRadius.clearAnimation();
            Animation animation = AnimationUtils.loadAnimation(this, R.anim.bottom_dismiss);
            mSbBlurRadius.setAnimation(animation);
            animation.setAnimationListener(new Animation.AnimationListener() {
                @Override
                public void onAnimationStart(Animation animation) {

                }

                @Override
                public void onAnimationEnd(Animation animation) {
                    mSbBlurRadius.setVisibility(View.GONE);
                }

                @Override
                public void onAnimationRepeat(Animation animation) {

                }
            });
            animation.start();
        }
    }
}
