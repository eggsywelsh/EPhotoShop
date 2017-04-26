package com.eggsy.photoshop;

/**
 * Created by eggsy on 17-3-31.
 */

public class NativeProcessor {

    /**
     * 图片灰化
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     */
    public static native int[] applyGray(int[] pixels, int width, int height);

    /**
     * 浮雕
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
    public static native int[] applyEmboss(int[] pixels, int width, int height);

    /**
     * 黑白
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
    public static native int[] applyBlackWhite(int[] pixels, int width, int height);

    /**
     * 底片
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
    public static native int[] applyPhotographicPlate(int[] pixels, int width, int height);

    /**
     * 模糊(高斯算法)
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
//    public static native int[] applyGaussianBlur(int[] pixels, int width, int height);

    /**
     * 快速模糊
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @param radius 模糊度
     * @return
     */
    public static native int[] applyFastBlur(int[] pixels, int width, int height,int radius);

    /**
     * 怀旧
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
    public static native int[] applyNostalgic(int[] pixels, int width, int height);


    /**
     * 对比度
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @return
     */
    public static native int[] applyContrast(int[] pixels, int width, int height,float contrast);

    /**
     * 亮度
     *
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @param brightness 亮度
     * @return
     */
    public static native int[] applyBrightness(int[] pixels, int width, int height,float brightness);

    /**
     * 饱和度
     * @param pixels 像素RGB数组
     * @param width 宽度范围
     * @param height 高度范围
     * @param level 饱和度
     * @return
     */
    public static native int[] applySaturation(int[] pixels, int width, int height,float level);

}
