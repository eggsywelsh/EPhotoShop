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

}
