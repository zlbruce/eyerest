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

#ifdef __cplusplus
extern "C" {
#endif

int state_init();

int state_timeout_cb(unsigned int time);

// 用于暂停计数
void state_active_pause();
void state_active_unpause();

#ifdef __cplusplus
}
#endif

#endif  /*__STATE_H__*/
