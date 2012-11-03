/*
 * =====================================================================================
 *
 *       Filename:  xevent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 10时23分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __XEVENT_H__
#define __XEVENT_H__

#include <glib.h>

G_BEGIN_DECLS

// 判断当前是否有鼠标键盘事件
gboolean xevent_has_event();

// 清除所有事件
void xevent_clear_event();

// 初始化
gboolean xevent_init();

// 运行监听线程
void xevent_run();

// 停止监听线程
void xevent_stop();


G_END_DECLS
#endif  /*__XEVENT_H__*/
