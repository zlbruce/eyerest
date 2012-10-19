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

#ifdef __cplusplus
extern "C"
{
#endif

// 判断当前是否有鼠标键盘事件
int xevent_has_event();

// 清除所有事件
void xevent_clear_event();

// 初始化
int xevent_init();

// 运行监听线程
void xevent_run();

// 停止监听线程
void xevent_stop();
#ifdef __cplusplus
}
#endif


#endif  /*__XEVENT_H__*/
