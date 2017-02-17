# 加解密组件库使用说明

	作者: daodaoliang
    时间: 2016年8月05日
    版本: 1.0.1.0
	邮箱: daodaoliang@yeah.net

[TOC]

## 1. 如何添加项目

* 首先拷贝源码到你的工程文件目录;
* 在你的项目 pro文件中添加:

```c
# import dll
win32: LIBS += -L$$PWD/../bin/ -lNEncryptionKit
DEPENDPATH += $$PWD/../bin

# import dll file
include($$PWD/../NEncryptionKit/NEncryptionKit_inc.pri)
```

** 具体的路径请按照你的项目情况进行修改**

## 2. 如何使用项目

* 创建加解密实例

```
	NEncryptionKit test_instance;
```

* MD5例子

```
    qDebug()<<"----------------------------MD5测试开始----------------------------";
    QString test_case_001("I am daodaoliang");
    QString test_encry_str = test_instance.getMD5Hash(test_case_001);
    qDebug()<<"MD5前的字符串:" << test_case_001;
    qDebug()<<"MD5后的字符串:" << test_encry_str;
    qDebug()<<"----------------------------MD5测试结束----------------------------";
```

* SHA加密实例

```
	qDebug()<<"----------------------------SHA测试开始----------------------------";
    QString test_case_002("I am nami");
    QString test_encry_str_002 = test_instance.getSHAHash(test_case_002);
    qDebug()<<"SHA前的字符串:" << test_case_002;
    qDebug()<<"SHA后的字符串:" << test_encry_str_002;
    qDebug()<<"----------------------------SHA测试结束----------------------------";
```

* 凯撒加密实例

```
	qDebug()<<"----------------------------Kaiser测试开始-------------------------";
    QString test_case_003("I am wangxiaowei");
    qint8 test_case_key(7);
    QString test_encry_str_003 = test_case_003;
    bool ret = test_instance.getByKaiser(test_case_003, test_case_key);
    qDebug()<<"加密是否成功:"<<ret;
    qDebug()<<"Kaiser前的字符串:" << test_encry_str_003;
    qDebug()<<"Kaiser后的字符串:" << test_case_003;
    ret = test_instance.getByKaiser(test_case_003, -test_case_key);
    qDebug()<<"解密是否成功:"<<ret;
    qDebug()<<"解密后的字符串:" << test_case_003;
    qDebug()<<"----------------------------Kaiser测试结束-------------------------";
```

* AES加解密实例

```
	qDebug()<<"----------------------------AES文件测试开始-------------------------";
    QString test_case_005("iamdaodaoliang");
    string test_case_006;
    QString test_case_007;
    test_instance.setPassword(QString("IamdaodaoliangSecret"));
    ret = test_instance.getEncryByAES(test_case_005,test_case_006);
    qDebug()<<"AES加密成功:"<<ret;
    qDebug()<<"加密前的数据:"<<test_case_005;
    qDebug()<<"加密后的数据:"<<QString::fromStdString(test_case_006);
    ret = test_instance.decryptByAES(test_case_006,test_case_007);
    qDebug()<<"AES解密成功:"<<ret;
    qDebug()<<"解密后的数据:"<<test_case_007;
    qDebug()<<"----------------------------AES文件测试结束-------------------------";
```

* RSA加解密实例

```
	qDebug()<<"----------------------------RSA文件测试开始-------------------------";
    QString test_case_pub = "./daodaoliang_test.pub";
    QString test_case_pri = "./daodaoliang_test.private";
    ret = test_instance.createRSAKey(test_case_pub, test_case_pri);
    qDebug()<<"是否产生密钥文件成功:"<<ret;
    QByteArray test_encrypt_str;
    QString test_decrypt_str;
    ret = test_instance.getEncryptByRSA("I am daodaoliang, my daughter is nami", test_encrypt_str, test_case_pub);
    qDebug()<<"RSA签名成功:"<<ret;
    qDebug()<<"RSA签名后的数据:"<<QString(test_encrypt_str);
    ret = test_instance.decryptionByRSA(test_encrypt_str,test_decrypt_str, test_case_pri);
    qDebug()<<"RSA解密成功:"<<ret;
    qDebug()<<"RSA解密后的数据:"<<test_decrypt_str;
    qDebug()<<"----------------------------RSA文件测试结束-------------------------";
```

## 3. 组件路线图

* 实现DES加解密;

## 4. changelog

* V 1.0.1.0 完成常用的加解密的封装;

