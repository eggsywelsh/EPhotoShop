### EPhotoShop

#### Introduce
Based on android NDK development, the use of C language to dynamically change the image of the RGB value, to achieve the purpose of real-time picture processing.
The initial built-in 9 in the transformation process, you can fork the project, and then run up to see the algorithm has been achieved.

#### How To Use
The main function please refer to `EPhotoShop` class, which encapsulates a variety of images to deal with the java method, the image processing algorithm using C language.
Of course, you can refer to the `EPhotoShop` class, write your own implementation and algorithms, you can also be based on the expansion, which some see your needs.

**call the image process method(by java)**
```
Bitmap newBitMap = srcBitmap.copy(srcBitmap.getConfig(), true);
EPhotoShop.doGray(newBitMap);  // do the gray transformation
mIvImg.setImageBitmap(newBitMap);  // set the new BitMap into ImageView
```
Also,you can call the `EPhotoShop` class's method as you want.

#### Sample
We use the above method(EPhotoShop.doGray(newBitMap)) to look at the whole process

**call method doGray**
```
    public static Bitmap doGray(Bitmap inputBitmap) {
        Bitmap outputImage = inputBitmap;

        int width = inputBitmap.getWidth();
        int height = inputBitmap.getHeight();
        // get transformation area pixels
        int[] pixels = new int[width * height];
        outputImage.getPixels(pixels, 0, width, 0, 0, width, height);
        // do transformate
        pixels = NativeProcessor.applyGray(pixels, width, height);
        try {
            outputImage.setPixels(pixels, 0, width, 0, 0, width, height);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return outputImage;
    }
```

**call the process method NativeProcessor.applyGray (by C)**
```
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
```

Through the above example, we know how to call the method from the java layer to deal with picture transformation, follow-up will have more algorithms to add to facilitate the use of everyone.
