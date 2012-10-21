/*
 * =====================================================================================
 *
 *       Filename:  eye_log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月21日 21时14分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#ifndef __EYE_LOG_H__
#define __EYE_LOG_H__

#define EYE_LOG_DEBUG       1
#define EYE_LOG_INFO        2
#define EYE_LOG_WARN        3
#define EYE_LOG_ERROR       4

#define eye_debug(msg...) eye_log(EYE_LOG_DEBUG, msg)
#define eye_info(msg...)  eye_log(EYE_LOG_INFO,  msg)
#define eye_warn(msg...)  eye_log(EYE_LOG_WARN,  msg)
#define eye_error(msg...) eye_log(EYE_LOG_ERROR, msg)

#ifdef __cplusplus
extern "C"
{
#endif

void eye_log(int level, const char* format, ...) __attribute__((__format__ (__printf__, 2, 3)));

#ifdef __cplusplus
}
#endif

#endif  /*__EYE_LOG_H__*/
