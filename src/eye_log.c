/*
 * =====================================================================================
 *
 *       Filename:  eye_log.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月21日 21时26分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */
#include <stdarg.h>
#include <stdio.h>

#include "eye_log.h"


void eye_log(int level, const char* format, ...)
{
    va_list args;

    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);

}
