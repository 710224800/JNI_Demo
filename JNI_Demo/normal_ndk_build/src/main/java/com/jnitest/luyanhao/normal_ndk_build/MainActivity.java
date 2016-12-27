package com.jnitest.luyanhao.normal_ndk_build;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private TextView text;
    private EditText str_edittext;
    private String str;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        text = (TextView) findViewById(R.id.text);

        str_edittext = (EditText) findViewById(R.id.str_edittext);

        str = "静态加载方式获取包名：" + JniTest.getPackname(MainActivity.this);

        str += "\n" + JNIDynamicUtils.getHelloStringFromJNI();

        str += "\n计算2 + 3 ：" + JNIDynamicUtils.getSumFromJNI(2, 3);


        text.setText(str);
    }

    public void buttonClicked(View v) {
        String str1;

        try {
            str1 = "\n正常返回，字符串长度：" + JNIDynamicUtils.getStrLength(str_edittext.getText().toString())
                    + "实际长度：" + str_edittext.getText().toString().length();
        } catch (NullPointerException e) {
            str1 = "\n空指针异常" + e.toString();
        } catch (IllegalArgumentException e) {
            str1 = "\n" + e.toString();
        }
        str += str1;
        text.setText(str);
    }

    public void gotoGrayImgeActivity(View v) {
        Intent intent = new Intent(this, GrayImageActivity.class);
        startActivity(intent);
    }

}
