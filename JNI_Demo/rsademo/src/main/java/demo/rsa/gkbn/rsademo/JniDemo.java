package demo.rsa.gkbn.rsademo;

/**
 * Created by gzbd on 2016/12/7.
 */

public class JniDemo {



    public   native  String MD5(String msg);

    public    native  String encodeAES(String msg);

    public    native  String decodeAES(String msg);


    public    native  String encryptDES(String msg);

    public    native  String decryptDES(String msg);

    public    native  String decryptRSA(String msg);

    public    native  String encryptRSA(String msg);

    public  native  String  encryptBase64(String msg);

    public  native  String  decryptBase64(String msg);

    static {
        System.loadLibrary("native");
    }



}
