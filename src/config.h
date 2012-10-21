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

#ifdef __cplusplus
extern "C" {
#endif

struct eye_config
{
    unsigned int interval;           // 间隔时间
    unsigned int rest_time;          // 每次休息时间
    unsigned int max_idle_time;      // 最长空闲时间，达到后停止计时
};

extern struct eye_config g_config;
int config_init();

int config_reinit(struct eye_config* config);

int config_write(struct eye_config* config);

#ifdef __cplusplus
}
#endif

#endif  /*__CONFIG_H__*/

