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
    gint x_coordinate;       // 显示文本的x坐标（文字的中心）
    gint y_coordinate;       // 显示文本的y坐标（文字的中心）
};

extern struct eye_config g_config;
gboolean config_init(int argc, char* argv[]);

//gboolean config_reinit(struct eye_config* config);

//gboolean config_write(struct eye_config* config);

G_END_DECLS
#endif  /*__CONFIG_H__*/

