# 配置操作组件库使用说明

	作者: daodaoliang
    时间: 2016年7月27日
    版本: 1.0.5.0
	邮箱: daodaoliang@yeah.net

[TOC]

## 1. 如何添加项目

* 首先拷贝源码到你的工程文件目录;
* 在你的项目 pro文件中添加:

```c
# import dll
win32: LIBS += -L$$PWD/../bin/ -lNConfig
DEPENDPATH += $$PWD/../bin

# import dll file
include($$PWD/../NConfig/NConfig_inc.pri)
```

** 具体的路径请按照你的项目情况进行修改**

## 2. 如何使用项目

* 初始化配置实例

```c
# 不存在则创建配置库时的初始化
NConfig::instance()->installAndInit("./test.conf", "daodaoliang", false);

# 使用已经存在的配置库的初始化
NConfig::instance()->installAndInit("./test.conf", "daodaoliang");
```

* 添加配置项内容

```c
NConfig::instance()->addConfigItem("nami","233333","MissU");
```

* 获取配置项内容

```c
QString tempValue;
NConfig::instance()->getConfigItem("nami","233333",tempValue);
```

* 清空配置项内容

```c
NConfig::instance()->clearConfig();
```

* 导出为ini类型的配置文件

```c
NConfig::instance()->exportConfigToFile();
```

* 从ini类型的配置文件导入到配置库

```c
NConfig::instance()->importConfigFromFile("./test.ini");
```

## 3. 组件路线图

* ~~增加配置库文件的导出为ini文件;~~
* ~~增加从ini文件导入为配置库文件;~~

## 4. changelog

* V 1.0.1.0 集成第三方加密sqlite库进行初始化项目;
* V 1.0.2.0 增加接口封装,实现初始化实例接口,增加项目配置接口,获取配置项目接口,清空配置接口,并编写测试用例;
* V 1.0.3.0 增加导出为ini文件的接口;
* V 1.0.4.0 增加从ini文件导入的接口;
* V 1.0.5.0 增加应用程序调用配置库的方法;
