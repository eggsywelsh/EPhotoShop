package com.eggsy.photoshop;

import android.graphics.Bitmap;

/**
 * Created by eggsy on 17-3-31.
 */

public class EPhotoShop {

    public static Bitmap doGray(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyGray(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

}
