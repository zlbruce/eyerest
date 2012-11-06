/*
 * =====================================================================================
 *
 *       Filename:  dbus.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月03日 01时16分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __DBUS_H__
#define __DBUS_H__

#include "eyerest-dbus.h"

G_BEGIN_DECLS

gboolean dbus_init();

void dbus_sent_status(guint time_remain, const gchar* state);

G_END_DECLS

#endif  /*__DBUS_H__*/
