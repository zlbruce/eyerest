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

#ifdef __cplusplus
extern "C" {
#endif

void xlock_lockscreen();

void xlock_unlockscreen();

#ifdef __cplusplus
}
#endif

#endif  /*__XLOCK_H__*/
