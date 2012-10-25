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
};

extern struct eye_config g_config;
gboolean config_init();

gboolean config_reinit(struct eye_config* config);

gboolean config_write(struct eye_config* config);

G_END_DECLS
#endif  /*__CONFIG_H__*/

