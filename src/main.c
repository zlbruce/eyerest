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
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "xevent.h"
#include "timer.h"
#include "config.h"
#include "eye_log.h"


int main(int argc, char* argv[]) 
{
    if (config_init() < 0)
    {
        eye_error("config_init failed!\n");
        return -1;
    }

    if (xevent_init() < 0)
    {
        eye_error("xevent_init failed!\n");
        return -1;
    }
    xevent_run();

    if(!state_init())
    {
        eye_error("state_init failed\n");
        return -1;
    }

    if (!timer_init())
    {
        eye_error("timer_init failed!\n");
        return -1;
    }
    timer_loop();
    return 0;
}

