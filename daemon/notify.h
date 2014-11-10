/*
 * =====================================================================================
 *
 *       Filename:  notify.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年11月14日 17时32分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __NOTIFY_H__
#define __NOTIFY_H__

#include <glib.h>

G_BEGIN_DECLS

gboolean notify_init();

void notify_timeout_cb(guint time);

G_END_DECLS
#endif  /*__NOTIFY_H__*/
