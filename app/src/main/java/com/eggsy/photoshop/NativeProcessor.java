package com.eggsy.photoshop;

/**
 * Created by eggsy on 17-3-31.
 */

public class NativeProcessor {

    /**
     * 图片灰化
     *
     * @param pixels
     * @param width
     * @param height
     */
    public static native int[] applyGray(int[] pixels, int width, int height);

    /**
     * 浮雕
     * @param pixels
     * @param width
     * @param height
     * @return
     */
    public static native int[] applyEmboss(int[] pixels, int width, int height);

    /**
     * 黑白
     * @param pixels
     * @param width
     * @param height
     * @return
     */
    public static native int[] applyBlackWhite(int[] pixels, int width, int height);

    /**
     * 底片
     * @param pixels
     * @param width
     * @param height
     * @return
     */
    public static native int[] applyPhotographicPlate(int[] pixels, int width, int height);

    /**
     * 模糊(高斯算法)
     * @param pixels
     * @param width
     * @param height
     * @return
     */
//    public static native int[] applyGaussianBlur(int[] pixels, int width, int height);

    /**
     * 快速模糊
     * @param pixels
     * @param width
     * @param height
     * @param radius
     * @return
     */
    public static native int[] applyFastBlur(int[] pixels, int width, int height,int radius);

    /**
     * 怀旧
     * @param pixels
     * @param width
     * @param height
     * @return
     */
    public static native int[] applyNostalgic(int[] pixels, int width, int height);


    /**
     * 对比度
     * @param pixels
     * @param width
     * @param height
     * @return
     */
    public static native int[] applyContrast(int[] pixels, int width, int height,float contrast);

    /**
     * 亮度
     * @param pixels
     * @param width
     * @param height
     * @param brightness
     * @return
     */
    public static native int[] applyBrightness(int[] pixels, int width, int height,float brightness);

    /**
     * 饱和度
     * @param pixels
     * @param width
     * @param height
     * @param level
     * @return
     */
    public static native int[] applySaturation(int[] pixels, int width, int height,float level);

}
