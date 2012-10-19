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

#ifdef __cplusplus
extern "C" {
#endif

    
void timer_stop_rest_dec();

void timer_start_rest_dec();

void timer_reset_rest();

int timer_init();

void timer_loop();

#ifdef __cplusplus
}
#endif

#endif  /*__TIMER_H__*/
