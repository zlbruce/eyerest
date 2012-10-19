/*
 * =====================================================================================
 *
 *       Filename:  moniter_x.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月18日 13时35分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>     /* getenv(), etc. */
#include <unistd.h>     /* sleep(), etc.  */
#include <signal.h>

#include "xevent.h"
#include "timer.h"
#include "config.h"


int main(int argc, char* argv[]) 
{
    if (config_init() < 0)
    {
        printf("config_init failed!\n");
        return -1;
    }

    if (xevent_init() < 0)
    {
        printf("xevent_init failed!\n");
        return -1;
    }
    xevent_run();

    if (timer_init() < 0)
    {
        printf("timer_init failed!\n");
        return -1;
    }
    timer_loop();
    return 0;
}
