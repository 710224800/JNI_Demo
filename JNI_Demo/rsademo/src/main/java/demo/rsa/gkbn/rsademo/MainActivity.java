package demo.rsa.gkbn.rsademo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.UUID;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView tv = (TextView) findViewById(R.id.sample_text);

        Button rsa = (Button) findViewById(R.id.button);
        Button des = (Button) findViewById(R.id.button5);

        Button aes = (Button) findViewById(R.id.button6);
        Button md5 = (Button) findViewById(R.id.button7);
        Button base64 = (Button) findViewById(R.id.button8);


        rsa.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText("密文："+ new JniDemo().encryptRSA("RSA加密测试-RSA加密测试-RSA加密测试-RSA加密测试"));
                tv.setText(tv.getText().toString() + "\n" + "明文："+ new JniDemo().decryptRSA(new JniDemo().encryptRSA("RSA加密测试-RSA加密测试-RSA加密测试-RSA加密测试")));
            }
        });

        des.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText("密文："+ new JniDemo().encryptDES("DES加密测试-DES加密测试-DES加密测试-DES加密测试"));
                tv.setText(tv.getText().toString() + "\n" + "明文："+ new JniDemo().decryptDES(new JniDemo().encryptDES("DES加密测试-DES加密测试-DES加密测试-DES加密测试")));
            }
        });

        aes.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText("密文："+ new JniDemo().encodeAES("AES加密测试-AES加密测试-AES加密测试-AES加密测试"));
                tv.setText(tv.getText().toString() + "\n" + "明文："+ new JniDemo().decodeAES(new JniDemo().encodeAES("AES加密测试-AES加密测试-AES加密测试-AES加密测试")));
            }
        });


        md5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText("密文："+ new JniDemo().MD5("MD5加密测试—MD5加密测试-MD5加密测试-MD5加密测试"));
                tv.setText(tv.getText().toString() + "\n" + "明文："+ "MD5加密测试—MD5加密测试-MD5加密测试-MD5加密测试");
            }
        });

        base64.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                tv.setText("密文："+ new JniDemo().encryptBase64("BASE64加密测试—BASE64加密测试-BASE64加密测试-BASE64加密测试"));
                tv.setText(tv.getText().toString() + "\n" + "明文："+ new JniDemo().decryptBase64(new JniDemo().encryptBase64("BASE64加密测试—BASE64加密测试-BASE64加密测试-BASE64加密测试")));
            }
        });

    }


}
