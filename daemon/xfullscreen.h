/*
 * =====================================================================================
 *
 *       Filename:  xfullscreen.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年11月12日 16时33分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __XFULLSCREEN_H__
#define __XFULLSCREEN_H__

#include <glib.h>

G_BEGIN_DECLS

// 初始化
gboolean xfullscreen_init();

// 是否有全屏窗口
gboolean xfullscreen_has_fullscreen();

G_END_DECLS
#endif  /*__XFULLSCREEN_H__*/
