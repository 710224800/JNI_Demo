package com.jnitest.luyanhao.normal_ndk_build;

import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class GrayImageActivity extends AppCompatActivity {

    private ImageView javaImg;
    private ImageView cImg;
    private TextView gray_img_result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gray_image);

        javaImg = (ImageView) findViewById(R.id.java_img);
        cImg = (ImageView) findViewById(R.id.c_img);

        gray_img_result = (TextView) findViewById(R.id.gray_img_result);
    }

    public void javaGray(View v) {
        long javaTimeBefore = System.currentTimeMillis();
        // 使用java代码把彩色像素转为灰度像素
        Bitmap bitmap = ConvertGrayImg(((BitmapDrawable) javaImg.getDrawable()).getBitmap());
        long javaTime = System.currentTimeMillis() - javaTimeBefore;
        //显示灰度图
        javaImg.setImageBitmap(bitmap);

        gray_img_result.setText(gray_img_result.getText().toString() + "\n" + "--->w:" + bitmap.getWidth() + ",h:"
                + bitmap.getHeight() + " JAVA TIME: " + javaTime + " ms");
    }

    public void cGray(View v) {
        long current = System.currentTimeMillis();
        // 先打开图像并读取像素
        Bitmap bitmap = ((BitmapDrawable) cImg.getDrawable()).getBitmap();
        int w = bitmap.getWidth();
        int h = bitmap.getHeight();
        int[] pix = new int[w * h];
        bitmap.getPixels(pix, 0, w, 0, 0, w, h);
        // 通过C++把彩色像素转为灰度像素
        int[] resultInt = JNIDynamicUtils.grayPic(pix, w, h);
        Bitmap resultImg = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);
        resultImg.setPixels(resultInt, 0, w, 0, 0, w, h);
        long ndkTime = System.currentTimeMillis() - current;
        // 显示灰度图
        cImg.setImageBitmap(resultImg);

        gray_img_result.setText(gray_img_result.getText().toString() + "\n" + "--->w:" + bitmap.getWidth() + ",h:"
                + bitmap.getHeight() + " NDK  TIME: " + ndkTime + " ms");
    }


    /**
     * java灰化图片
     *
     * @param img1
     * @return
     */
    public Bitmap ConvertGrayImg(Bitmap img1) {

        int w = img1.getWidth(), h = img1.getHeight();
        int[] pix = new int[w * h];
        img1.getPixels(pix, 0, w, 0, 0, w, h);

        int alpha = 0xFF << 24;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                // 获得像素的颜色
                int color = pix[w * i + j];
                int red = ((color & 0x00FF0000) >> 16);
                int green = ((color & 0x0000FF00) >> 8);
                int blue = color & 0x000000FF;
                color = (red + green + blue) / 3;
                color = alpha | (color << 16) | (color << 8) | color;
                pix[w * i + j] = color;
            }
        }
        Bitmap result = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);
        result.setPixels(pix, 0, w, 0, 0, w, h);
        return result;
    }
}
