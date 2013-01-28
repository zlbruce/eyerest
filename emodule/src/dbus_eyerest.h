/*
 * =====================================================================================
 *
 *       Filename:  dbus_eyerest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年01月28日 09时38分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __DBUS_EYEREST_H__
#define __DBUS_EYEREST_H__
#include <stdint.h>

typedef void (*eyerest_state_cb)(uint32_t time_remain, const char* state, void* ctx);

int eyerest_dbus_init(eyerest_state_cb cb, void* ctx);
int eyerest_dbus_shutdown();

void eyerest_dbus_pause();
void eyerest_dbus_unpause();
void eyerest_dbus_rest_now();
void eyerest_dbus_delay(uint32_t t);

#endif  /*__DBUS_EYEREST_H__*/
