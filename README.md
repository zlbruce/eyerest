#eyerest

eyerest是一款通过定时锁定屏幕，提醒用户休息的小软件

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
 3. 休息前提醒
 
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

    make install

安装文件如下：

* dbus service文件：org.zlbruce.eyerest.service
* eyerest-daemon
* eyerest-cli

###运行

直接执行`eyerest-daemon`

源代码目录中有一份配置文件示例，可以拷贝到`$HOME/.config/eyerest.conf`中进行修改，修改完成后需要重启软件。

###Gnome Shell Extension

附带一个简单的 Gnome Shell 扩展，只在我的 Gnome Shell 3.4.2 中进行过测试。

安装之后会在顶部菜单中增加一个按钮，按钮显示倒计时，点击按钮后弹出一组菜单，用于控制 eyerest-daemon，可以参看截图。

![Gnome Shell Extension Eyerest Menu](http://i.imgur.com/oV3DG.png)

离休息时间还剩 1 分钟时会进行提示，如图：

![Gnome Shell Extension Eyerest Notify](http://i.imgur.com/oV3DG.png)

将源代码目录下的`gnome-shell-extension-eyerest/eyerest@zlbruce.org`整个目录拷贝到`$HOME/.local/share/gnome-shell/extensions/`目录，然后重启 gnome-shell，开启这个扩展即可。
