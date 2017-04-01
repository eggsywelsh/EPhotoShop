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

    public static Bitmap doEmboss(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyEmboss(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doBlackWhite(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyBlackWhite(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doPhotographicPlate(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyPhotographicPlate(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doFastBlur(Bitmap inputBitmap, int radius) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyFastBlur(pixels, width, height, radius);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doNostalgic(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyNostalgic(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doContrast(Bitmap inputBitmap, int contrast) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyContrast(pixels, width, height, contrast);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doBrightness(Bitmap inputBitmap, int brightness) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applyBrightness(pixels, width, height, brightness);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

    public static Bitmap doSaturation(Bitmap inputBitmap, int level) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();

        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        pixels = NativeProcessor.applySaturation(pixels, width, height, level);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }

}
