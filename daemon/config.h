/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  配置文件
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 14时18分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <glib.h>

G_BEGIN_DECLS

struct eye_config
{
    gint interval;           // 间隔时间
    gint rest_time;          // 每次休息时间
    gint max_idle_time;      // 最长空闲时间，达到后停止计时

    // 显示倒计时
    gchar* font;             // 使用的字体
    gchar* color;            // 使用的颜色
    gchar* format;           // 显示的内容
    gint x_coordinate;       // 显示文本的x坐标（文字的中心）
    gint y_coordinate;       // 显示文本的y坐标（文字的中心）

    // 其他
    gboolean foreground;     // 前台运行，不挂到后台

    // notify 配置相关
    gchar* notify_format;    // 提示信息的格式
    gint notify_time;        // 提前通知时间
    gint notify_action;      // 是否发送 Notify Action
};

extern struct eye_config g_config;

gboolean config_init(int argc, char* argv[]);

//void config_destroy();

//gboolean config_reinit(struct eye_config* config);

//gboolean config_write(struct eye_config* config);

G_END_DECLS
#endif  /*__CONFIG_H__*/

