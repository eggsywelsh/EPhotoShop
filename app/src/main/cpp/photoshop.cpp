#include <jni.h>
#include <string>
#include <android/log.h>


extern "C" {

#include "filter.h"
#include "android_log.h"
#include <math.h>
#include <stdlib.h>

static int max(int x,int y){
    return x > y ? x : y;
}

static int min(int x,int y){
    return x > y ? y : x;
}

int alpha(int color) {
    return (color >> 24) & 0xFF;
}
int red(int color) {
    return (color >> 16) & 0xFF;
}
int green(int color) {
    return (color >> 8) & 0xFF;
}
int blue(int color) {
    return color & 0xFF;
}
int ARGB(int alpha, int red, int green, int blue) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

JNIEXPORT jstring JNICALL Java_com_eggsy_photoshop_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_eggsy_photoshop_MainActivity_test(JNIEnv *env, jobject instance) {
    std::string test = "test from C++";
    return env->NewStringUTF(test.c_str());
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyGray(JNIEnv *env, jclass type,
                                                             jintArray pixels_, jint width,
                                                             jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    jint rbuf[newSize];

    int widthIndex = 0, heightIndex = 0;

    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            int curr_color = pixels[heightIndex * width + widthIndex];
            int r = red(curr_color);
            int g = green(curr_color);
            int b = blue(curr_color);
            int modif_color = (int) (r * 0.3 + g * 0.59 + b * 0.11);
            rbuf[heightIndex * width + widthIndex] = ARGB(alpha(curr_color), modif_color,
                                                          modif_color, modif_color);
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, rbuf);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyEmboss(JNIEnv *env, jclass type,
                                                               jintArray pixels_, jint width,
                                                               jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;
    jint rbuf[newSize];

    int preColor = pixels[0], prepreColor = 0, widthIndex = 0, heightIndex = 0;

    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            int curr_color = pixels[heightIndex * width + widthIndex];
            int r = red(curr_color) - red(prepreColor) + 128;
            int g = green(curr_color) - red(prepreColor) + 128;
            int b = green(curr_color) - blue(prepreColor) + 128;
            int a = alpha(curr_color);

            int newcolor = (int) (r * 0.3 + g * 0.59 + b * 0.11);

            int modif_color = ARGB(a, newcolor, newcolor, newcolor);
            rbuf[heightIndex * width + widthIndex] = modif_color;
            prepreColor = preColor;
            preColor = curr_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, rbuf);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyBlackWhite(JNIEnv *env, jclass type,
                                                                   jintArray pixels_, jint width,
                                                                   jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;
    jint rbuf[newSize]; // 新图像像素值

    int widthIndex = 0, heightIndex = 0, iPixel = 0;
    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            int curr_color = pixels[heightIndex * width + widthIndex];

            int avg = (red(curr_color) + green(curr_color) + blue(curr_color))
                      / 3;
            if (avg >= 100) {
                iPixel = 255;
            } else {
                iPixel = 0;
            }
            int modif_color = ARGB(255, iPixel, iPixel, iPixel);
            rbuf[heightIndex * width + widthIndex] = modif_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, rbuf);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyPhotographicPlate(JNIEnv *env, jclass type,
                                                                          jintArray pixels_,
                                                                          jint width, jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;
    jint rbuf[newSize];

    int widthIndex = 0, heightIndex = 0;
    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            int curr_color = pixels[heightIndex * width + widthIndex];

            int r = 255 - red(curr_color);
            int g = 255 - green(curr_color);
            int b = 255 - blue(curr_color);
            int a = alpha(curr_color);
            int modif_color = ARGB(a, r, g, b);
            rbuf[heightIndex * width + widthIndex] = modif_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, rbuf);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyFastBlur(JNIEnv *env, jclass type,
                                                                 jintArray pixels_, jint width,
                                                                 jint height, jint radius) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    const int newSize = width * height;

//    jint rbuf[newSize];

    int wm = width - 1;
    int hm = height - 1;

    int div = radius + radius + 1;

    int r[newSize],g[newSize], b[newSize];

    int rsum, gsum, bsum, x, y, i, p, yp, yi, yw;

    int vmin[max(width, height)];

    int divsum = (div + 1) >> 1;
    divsum *= divsum;
    int dv[256 * divsum];
    for (i = 0; i < 256 * divsum; i++) {
        dv[i] = (i / divsum);
    }

    yw = yi = 0;

    int stack[div][3];
    int stackpointer;
    int stackstart;
    int * sir;
    int rbs;
    int r1 = radius + 1;
    int routsum, goutsum, boutsum;
    int rinsum, ginsum, binsum;

    for (y = 0; y < height; y++) {
        rinsum = ginsum = binsum = routsum = goutsum = boutsum = rsum = gsum = bsum = 0;
        for (i = -radius; i <= radius; i++) {
            p = pixels[yi + min(wm, max(i, 0))];
            sir = stack[i + radius];
            sir[0] = (p & 0xff0000) >> 16;
            sir[1] = (p & 0x00ff00) >> 8;
            sir[2] = (p & 0x0000ff);
            rbs = r1 - abs(i);
            rsum += sir[0] * rbs;
            gsum += sir[1] * rbs;
            bsum += sir[2] * rbs;
            if (i > 0) {
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
            } else {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
            }
        }
        stackpointer = radius;

        for (x = 0; x < width; x++) {

            r[yi] = dv[rsum];
            g[yi] = dv[gsum];
            b[yi] = dv[bsum];

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;

            stackstart = stackpointer - radius + div;
            sir = stack[stackstart % div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];

            if (y == 0) {
                vmin[x] = min(x + radius + 1, wm);
            }
            p = pixels[yw + vmin[x]];

            sir[0] = (p & 0xff0000) >> 16;
            sir[1] = (p & 0x00ff00) >> 8;
            sir[2] = (p & 0x0000ff);

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;

            stackpointer = (stackpointer + 1) % div;
            sir = stack[(stackpointer) % div];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];

            yi++;
        }
        yw += width;
    }
    for (x = 0; x < width; x++) {
        rinsum = ginsum = binsum = routsum = goutsum = boutsum = rsum = gsum = bsum = 0;
        yp = -radius * width;
        for (i = -radius; i <= radius; i++) {
            yi = max(0, yp) + x;

            sir = stack[i + radius];

            sir[0] = r[yi];
            sir[1] = g[yi];
            sir[2] = b[yi];

            rbs = r1 - abs(i);

            rsum += r[yi] * rbs;
            gsum += g[yi] * rbs;
            bsum += b[yi] * rbs;

            if (i > 0) {
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
            } else {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
            }

            if (i < hm) {
                yp += width;
            }
        }
        yi = x;
        stackpointer = radius;
        for (y = 0; y < height; y++) {
            // Preserve alpha channel: ( 0xff000000 & pix[yi] )
            pixels[yi] = (0xff000000 & pixels[yi]) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;

            stackstart = stackpointer - radius + div;
            sir = stack[stackstart % div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];

            if (x == 0) {
                vmin[y] = min(y + r1, hm) * width;
            }
            p = x + vmin[y];

            sir[0] = r[p];
            sir[1] = g[p];
            sir[2] = b[p];

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;

            stackpointer = (stackpointer + 1) % div;
            sir = stack[stackpointer];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];

            yi += width;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);
    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}



}

