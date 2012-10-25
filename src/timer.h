/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 11时20分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <glib.h>

G_BEGIN_DECLS

gboolean timer_init();

void timer_loop();

G_END_DECLS

#endif  /*__TIMER_H__*/
