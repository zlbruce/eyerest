#eyerest

[![Build Status](https://travis-ci.org/zlbruce/eyerest.svg?branch=master)](https://travis-ci.org/zlbruce/eyerest)

eyerest是一款通过定时锁定屏幕，提醒用户休息的小软件

相关项目：
* [zlbruce/eyerest-gnome-shell-extension](https://github.com/zlbruce/eyerest-gnome-shell-extension)
* [zlbruce/eyerest-systray](https://github.com/zlbruce/eyerest-systray)

**请使用最新的 tag 编译**

##功能

* 定时锁定屏幕一定时间
* 根据是否有鼠标与键盘事件检测用户是否离开
* 可配置间隔时间，锁屏时间，空闲时间
* 可配置锁屏时屏幕上显示的文字，位置，字体，大小与颜色
* 提供dbus接口，可以进行暂停，推迟等

###TODO

* 增加dbus接口（完成）
* 根据dbus接口实现
 1. 显示剩余时间（完成）
 2. 推迟休息（完成）
 3. 休息前提醒（完成）
* Gnome Shell Extension（完成）
* KDE PLASMA（完成）
 
##编译与运行

###依赖

* x11
* xtst
* xft
* glib-2.0
* gio-2.0

###编译

进入代码目录，然后执行：

    cmake .
    make

如果想安装，也可以执行：

    sudo make install

安装文件如下：

* dbus service文件：org.zlbruce.eyerest.service
* eyerest-daemon
* eyerest-cli

###运行

直接执行`eyerest-daemon`

源代码目录中有一份配置文件示例，可以拷贝到`$HOME/.config/eyerest.conf`中进行修改，修改完成后需要重启软件。

