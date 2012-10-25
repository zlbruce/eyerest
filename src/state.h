/*
 * =====================================================================================
 *
 *       Filename:  state.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月22日 21时41分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __STATE_H__
#define __STATE_H__

#include <glib.h>

G_BEGIN_DECLS

gboolean state_init();

void state_timeout_cb(guint time);

// 用于暂停计数
void state_active_pause();
void state_active_unpause();

G_END_DECLS
#endif  /*__STATE_H__*/
