#include <jni.h>
#include <string>

extern "C" {

#include "android_log.h"
#include <math.h>
#include <stdlib.h>

static int max(int x, int y) {
    return x > y ? x : y;
}

static int min(int x, int y) {
    return x > y ? y : x;
}

static int alpha(int color) {
    return (color >> 24) & 0xFF;
}
static int red(int color) {
    return (color >> 16) & 0xFF;
}
static int green(int color) {
    return (color >> 8) & 0xFF;
}
static int blue(int color) {
    return color & 0xFF;
}
static int ARGB(int alpha, int red, int green, int blue) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

static void
HSLtoRGB_Subfunction(unsigned int &c, const float &temp1, const float &temp2, const float &temp3) {
    if ((temp3 * 6) < 1)
        c = (unsigned int) ((temp2 + (temp1 - temp2) * 6 * temp3) * 100);
    else if ((temp3 * 2) < 1)
        c = (unsigned int) (temp1 * 100);
    else if ((temp3 * 3) < 2)
        c = (unsigned int) ((temp2 + (temp1 - temp2) * (.66666 - temp3) * 6) * 100);
    else
        c = (unsigned int) (temp2 * 100);
    return;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyGray(JNIEnv *env, jclass type,
                                                   jintArray pixels_, jint width,
                                                   jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    int widthIndex = 0, heightIndex = 0, r, g, b, modif_color, curr_color;

    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            curr_color = pixels[heightIndex * width + widthIndex];
            r = red(curr_color);
            g = green(curr_color);
            b = blue(curr_color);
            modif_color = (int) (r * 0.3 + g * 0.59 + b * 0.11);
            pixels[heightIndex * width + widthIndex] = ARGB(alpha(curr_color), modif_color,
                                                            modif_color, modif_color);
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyEmboss(JNIEnv *env, jclass type,
                                                     jintArray pixels_, jint width,
                                                     jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    int preColor = pixels[0], prepreColor = 0, widthIndex = 0, heightIndex = 0, r, g, b, a, curr_color, newcolor, modif_color;

    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            curr_color = pixels[heightIndex * width + widthIndex];
            r = red(curr_color) - red(prepreColor) + 128;
            g = green(curr_color) - red(prepreColor) + 128;
            b = green(curr_color) - blue(prepreColor) + 128;
            a = alpha(curr_color);

            newcolor = (int) (r * 0.3 + g * 0.59 + b * 0.11);

            modif_color = ARGB(a, newcolor, newcolor, newcolor);
            pixels[heightIndex * width + widthIndex] = modif_color;
            prepreColor = preColor;
            preColor = curr_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyBlackWhite(JNIEnv *env, jclass type,
                                                         jintArray pixels_, jint width,
                                                         jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

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
            pixels[heightIndex * width + widthIndex] = modif_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyPhotographicPlate(JNIEnv *env, jclass type,
                                                                jintArray pixels_,
                                                                jint width, jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    int widthIndex = 0, heightIndex = 0;
    for (widthIndex = 0; widthIndex < width; widthIndex++) {
        for (heightIndex = 0; heightIndex < height; heightIndex++) {
            int curr_color = pixels[heightIndex * width + widthIndex];

            int r = 255 - red(curr_color);
            int g = 255 - green(curr_color);
            int b = 255 - blue(curr_color);
            int a = alpha(curr_color);
            int modif_color = ARGB(a, r, g, b);
            pixels[heightIndex * width + widthIndex] = modif_color;
        }
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyFastBlur(JNIEnv *env, jclass type,
                                                       jintArray pixels_, jint width,
                                                       jint height, jint radius) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    const int newSize = width * height;

    int wm = width - 1;
    int hm = height - 1;

    int div = radius + radius + 1;

    int r[newSize], g[newSize], b[newSize];

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
    int *sir;
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

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyNostalgic(JNIEnv *env, jclass type, jintArray pixels_,
                                                        jint width, jint height) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    const int newSize = width * height;

    int widthIndex = 0, heightIndex = 0, curr_color, r, g, b, nr, ng, nb;

    for (widthIndex = 0; widthIndex < height; widthIndex++) {
        for (heightIndex = 0; heightIndex < width; heightIndex++) {
            curr_color = pixels[width * widthIndex + heightIndex];
            r = red(curr_color);
            g = green(curr_color);
            b = blue(curr_color);
            nr = (int) (0.393 * r + 0.769 * g + 0.189 * b);
            ng = (int) (0.349 * r + 0.686 * g + 0.168 * b);
            nb = (int) (0.272 * r + 0.534 * g + 0.131 * b);
            int newColor = ARGB(255, nr > 255 ? 255 : nr, ng > 255 ? 255 : ng, nb > 255 ? 255 : nb);
            pixels[width * widthIndex + heightIndex] = newColor;
        }
    }

    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}
JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyContrast(JNIEnv *env, jclass type, jintArray pixels_,
                                                       jint width, jint height, jfloat value) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int a, r, g, b;

    int newSize = width * height;

    for (int i = 0; i < width * height; i++) {
        a = alpha(pixels[i]);
        r = red(pixels[i]);
        g = green(pixels[i]);
        b = blue(pixels[i]);

        r = (((((r / 255.0) - 0.5) * value) + 0.5) * 255.0);
        g = (((((g / 255.0) - 0.5) * value) + 0.5) * 255.0);
        b = (((((b / 255.0) - 0.5) * value) + 0.5) * 255.0);

        // validation check
        if (r > 255)
            r = 255;
        else if (r < 0)
            r = 0;

        if (g > 255)
            g = 255;
        else if (g < 0)
            g = 0;

        if (b > 255)
            b = 255;
        else if (b < 0)
            b = 0;

        pixels[i] = ARGB(a, r, g, b);
    }
    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applyBrightness(JNIEnv *env, jclass type,
                                                         jintArray pixels_, jint width, jint height,
                                                         jfloat brightness) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    int a, r, g, b;

    for (int i = 0; i < width * height; i++) {
        a = alpha(pixels[i]);
        r = red(pixels[i]);
        g = green(pixels[i]);
        b = blue(pixels[i]);

        r += brightness;
        g += brightness;
        b += brightness;

        // validation check
        if (r > 255)
            r = 255;
        else if (r < 0)
            r = 0;

        if (g > 255)
            g = 255;
        else if (g < 0)
            g = 0;

        if (b > 255)
            b = 255;
        else if (b < 0)
            b = 0;

        pixels[i] = ARGB(a, r, g, b);
    }

    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}

JNIEXPORT jintArray JNICALL
Java_com_eggsy_photoshop_NativeProcessor_applySaturation(JNIEnv *env, jclass type,
                                                         jintArray pixels_, jint width, jint height,
                                                         jfloat level) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);

    int newSize = width * height;

    unsigned int a;
    unsigned int r;
    unsigned int g;
    unsigned int b;

    float temp1, temp2, temp3;

    float r_percent;
    float g_percent;
    float b_percent;

    float max_color, min_color;
    float L, S, H;

    for (int i = 0; i < width * height; i++) {
        a = alpha(pixels[i]);
        r = red(pixels[i]);
        g = green(pixels[i]);
        b = blue(pixels[i]);

        r_percent = ((float) r) / 255;
        g_percent = ((float) g) / 255;
        b_percent = ((float) b) / 255;

        max_color = 0;
        if ((r_percent >= g_percent) && (r_percent >= b_percent)) {
            max_color = r_percent;
        }
        if ((g_percent >= r_percent) && (g_percent >= b_percent))
            max_color = g_percent;
        if ((b_percent >= r_percent) && (b_percent >= g_percent))
            max_color = b_percent;

        min_color = 0;
        if ((r_percent <= g_percent) && (r_percent <= b_percent))
            min_color = r_percent;
        if ((g_percent <= r_percent) && (g_percent <= b_percent))
            min_color = g_percent;
        if ((b_percent <= r_percent) && (b_percent <= g_percent))
            min_color = b_percent;

        L = 0;
        S = 0;
        H = 0;

        L = (max_color + min_color) / 2;

        if (max_color == min_color) {
            S = 0;
            H = 0;
        } else {
            if (L < .50) {
                S = (max_color - min_color) / (max_color + min_color);
            } else {
                S = (max_color - min_color) / (2 - max_color - min_color);
            }
            if (max_color == r_percent) {
                H = (g_percent - b_percent) / (max_color - min_color);
            }
            if (max_color == g_percent) {
                H = 2 + (b_percent - r_percent) / (max_color - min_color);
            }
            if (max_color == b_percent) {
                H = 4 + (r_percent - g_percent) / (max_color - min_color);
            }
        }
        S = (unsigned int) (S * 100);
        L = (unsigned int) (L * 100);
        H = H * 60;
        if (H < 0)
            H += 360;

        S *= level;
        if (S > 100) {
            S = 100;
        } else if (S < 0) {
            S = 0;
        }

        L = ((float) L) / 100;
        S = ((float) S) / 100;
        H = ((float) H) / 360;

        if (S == 0) {
            r = L * 100;
            g = L * 100;
            b = L * 100;
        } else {
            temp1 = 0;
            if (L < .50) {
                temp1 = L * (1 + S);
            } else {
                temp1 = L + S - (L * S);
            }

            temp2 = 2 * L - temp1;

            temp3 = 0;
            for (int i = 0; i < 3; i++) {
                switch (i) {
                    case 0: // red
                    {
                        temp3 = H + .33333f;
                        if (temp3 > 1)
                            temp3 -= 1;
                        HSLtoRGB_Subfunction(r, temp1, temp2, temp3);
                        break;
                    }
                    case 1: // green
                    {
                        temp3 = H;
                        HSLtoRGB_Subfunction(g, temp1, temp2, temp3);
                        break;
                    }
                    case 2: // blue
                    {
                        temp3 = H - .33333f;
                        if (temp3 < 0)
                            temp3 += 1;
                        HSLtoRGB_Subfunction(b, temp1, temp2, temp3);
                        break;
                    }
                    default: {
                    }
                }
            }
        }
        r = (unsigned int) ((((float) r) / 100) * 255);
        g = (unsigned int) ((((float) g) / 100) * 255);
        b = (unsigned int) ((((float) b) / 100) * 255);

        pixels[i] = ARGB(a, r, g, b);

    }

    jintArray result = env->NewIntArray(newSize);
    env->SetIntArrayRegion(result, 0, newSize, pixels);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    return result;
}


}

