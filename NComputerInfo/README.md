# 电脑运行信息组件使用说明

[TOC]

## 0.如何添加项目

* 首先拷贝源码到你的工程文件目录;
* 在你的项目 pro文件中添加:

```c
# import dll
win32: LIBS += -L$$PWD/../bin/ -lNComputerInfo
DEPENDPATH += $$PWD/../bin

# import dll file
include($$PWD/../NComputerInfo/NComputerInfo_inc.pri)
```

** 具体的路径请按照你的项目情况进行修改**

## 1. 测试用例

* 获取硬件信息

```
	NComputerInfo test_case_instance;

    qDebug()<<"---------------------获取MAC用例开始------------------------";
    QString test_case_001_mac;
    bool ret = test_case_instance.getMAC(test_case_001_mac, false);
    qDebug()<<"是否获取成功:"<<ret<<" MAC:"<<test_case_001_mac;
    qDebug()<<"---------------------获取MAC用例结束------------------------";

    qDebug()<<"---------------------获取C盘逻辑序列号用例开始-----------------";
    QString test_case_002_serial;
    ret = test_case_instance.getVolumeSerialNumber(test_case_002_serial);
    qDebug()<<"是否获取成功:"<<ret<<" serial:"<<test_case_002_serial;
    qDebug()<<"---------------------获取C盘逻辑序列号用例结束-----------------";

    qDebug()<<"---------------------获取硬盘物理序列号用例开始-----------------";
    QString test_case_003_serial;
    ret = test_case_instance.getHardDiskSerialNumber(test_case_003_serial);
    qDebug()<<"是否获取成功:"<<ret<<" serial:"<<test_case_003_serial;
    qDebug()<<"---------------------获取硬盘物理序列号用例结束-----------------";

    qDebug()<<"---------------------获取CPU个数用例开始----------------------";
    QString test_case_004_count;
    ret = test_case_instance.getCPUCount(test_case_004_count);
    qDebug()<<"是否获取成功:"<<ret<<" count:"<<test_case_004_count;
    qDebug()<<"---------------------获取CPU个数用例结束----------------------";

    qDebug()<<"---------------------获取硬盘尺寸用例开始----------------------";
    int test_case_006_total_size;
    int test_case_006_ava_size;
    ret = test_case_instance.getDiskSize(test_case_006_total_size, test_case_006_ava_size);
    qDebug()<<"是否获取成功:"<<ret<<" total:"<<test_case_006_total_size<<" available:"<<test_case_006_ava_size;
    qDebug()<<"---------------------获取硬盘尺寸用例结束----------------------";
```

* 获取系统信息

```
	NComputerInfo test_case_instance;

	qDebug()<<"---------------------获取系统版本用例开始----------------------";
    QString test_case_005_version;
    ret = test_case_instance.getSysVersion(test_case_005_version);
    qDebug()<<"是否获取成功:"<<ret<<" version:"<<test_case_005_version;
    qDebug()<<"---------------------获取系统版本用例结束----------------------";

    qDebug()<<"---------------------获取使用率用例开始------------------------";
    QString test_case_007_rate;
    ret = test_case_instance.getUsageRate(test_case_007_rate);
    qDebug()<<"是否获取成功:"<<ret<<" rate:"<<test_case_007_rate;
    qDebug()<<"---------------------获取使用率用例结束------------------------";

    qDebug()<<"---------------------获取CPU版本用例开始----------------------";
    QString test_case_008_version;
    ret = test_case_instance.getCPUVersion(test_case_008_version);
    qDebug()<<"是否获取成功:"<<ret<<" cpu version:"<<test_case_008_version;
    qDebug()<<"---------------------获取CPU版本用例结束----------------------";

    qDebug()<<"---------------------获取运行用例开始-------------------------";
    qDebug()<<"系统当前运行时间:"<<test_case_instance.getRuningTime();
    qDebug()<<"---------------------获取运行用例结束-------------------------";

    qDebug()<<"---------------------获取CPU架构用例开始-----------------------";
    QString test_case_009_arch;
    ret = test_case_instance.getCPUArch(test_case_009_arch);
    qDebug()<<"是否获取成功:"<<ret<<" 架构:"<<test_case_009_arch;
    qDebug()<<"---------------------获取CPU架构用例结束-----------------------";

    qDebug()<<"---------------------获取系统登录用户用例开始--------------------";
    QString test_case_010_user;
    ret = test_case_instance.getSysUserName(test_case_010_user);
    qDebug()<<"是否获取成功:"<<ret<<" 架构:"<<test_case_010_user;
    qDebug()<<"---------------------获取系统登录用户用例开始--------------------";

```

* 机器码信息获取和验证

```
	NComputerInfo test_case_instance;

    qDebug()<<"---------------------获取机器码用例开始-------------------------";
    QString test_case_011_machine_code;
    ret = test_case_instance.getMachineCode(test_case_011_machine_code);
    qDebug()<<"是否获取成功:"<<ret<<" 机器码:"<<test_case_011_machine_code;
    qDebug()<<"---------------------获取机器码用例结束-------------------------";

    qDebug()<<"---------------------验证机器码用例开始-------------------------";
    NComputerInfo::MACHINE_CODE_ERROR test_case_012_machine_code;
    ret = test_case_instance.verifiMachineCode(test_case_011_machine_code, test_case_012_machine_code);
    qDebug()<<"是否验证成功:"<<ret<<" 错误代码:"<<test_case_012_machine_code;
    qDebug()<<"---------------------验证机器码用例结束-------------------------";
```

* 网络信息的获取

```
	NComputerInfo test_case_instance;
    
	qDebug()<<"---------------------验证外网地址用例开始------------------------";
    qDebug()<<"外网地址为:"<<test_case_instance.getWlanIP();
    qDebug()<<"---------------------验证外网地址用例结束------------------------";

    qDebug()<<"---------------------验证本地地址用例开始------------------------";
    qDebug()<<"本地地址为:"<<test_case_instance.getLocalIP();
    qDebug()<<"---------------------验证本地地址用例结束------------------------";

    qDebug()<<"---------------------验证联通外网用例开始------------------------";
    qDebug()<<"是否联通外网:"<<test_case_instance.isConnectedWlan();
    qDebug()<<"---------------------验证联通外网用例开始------------------------";
```

## 2. 组件路线图

* ~~获取硬盘逻辑序列号信息;~~
* ~~获取CPU架构信息;~~
* ~~获取CPU个数信息;~~
* ~~获取CPU版本信息;~~
* ~~获取MAC地址信息;~~
* ~~获取硬盘使用量信息;~~
* ~~获取系统版本信息;~~
* ~~获取系统登录用户信息;~~
* ~~获取机器码信息;~~
* ~~解析验证机器码信息;~~
* ~~获取外网地址信息;~~
* ~~获取内网地址信息;~~
* ~~提供是否联通外网接口;~~
* ~~获取CPU和内存使用率信息;~~
* 获取硬盘物理序列号;
* 获取内存序列号;
* 获取显卡相关信息;

## 3. changelog

* V 1.0.1.0 完成常用的硬件信息获取封装;
* V 1.0.2.0 完成常用系统信息获取封装;
* V 1.0.3.0 增加机器码的获取打包和解析;
* V 1.0.4.0 增加网络信息获取的封装;



