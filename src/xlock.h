/*
 * =====================================================================================
 *
 *       Filename:  xlock.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月21日 22时44分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __XLOCK_H__
#define __XLOCK_H__

#include <glib.h>

G_BEGIN_DECLS

void xlock_lockscreen();

void xlock_unlockscreen();

void xlock_display_time(time_t time);

G_END_DECLS

#endif  /*__XLOCK_H__*/
