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

#include <glib.h>

#include "xevent.h"
#include "timer.h"
#include "config.h"




int main(int argc, char* argv[]) 
{

    if (!config_init(argc, argv))
    {
        g_print("config_init failed!\n");
        return -1;
    }

    if (!xevent_init())
    {
        g_error("xevent_init failed!\n");
        return -1;
    }
    xevent_run();

    if(!state_init())
    {
        g_error("state_init failed\n");
        return -1;
    }

    if (!timer_init())
    {
        g_error("timer_init failed!\n");
        return -1;
    }
    timer_loop();
    return 0;
}

