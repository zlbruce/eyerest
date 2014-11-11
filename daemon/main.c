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
#include <locale.h>

#include <glib.h>

#include "xevent.h"
#include "timer.h"
#include "config.h"
#include "dbus.h"
#include "state.h"
#include "notify.h"


int main(int argc, char* argv[]) 
{
    setlocale (LC_ALL, "");
    g_type_init();
    g_set_application_name ("eyerest-daemon");

    if (!config_init(argc, argv))
    {
        g_critical("config_init failed!\n");
        return -1;
    }

    if(!g_config.foreground)
    {
        daemon(0, 0);
    }

    if(!dbus_init())
    {
        g_critical("dbus_init failed!\n");
    }

    if (!notify_init())
    {
        g_critical("notify_init failed!\n");
    }

    if (!xevent_init())
    {
        g_critical("xevent_init failed!\n");
        return -1;
    }
    xevent_run();

    if(!state_init())
    {
        g_critical("state_init failed\n");
        return -1;
    }

    if (!timer_init())
    {
        g_critical("timer_init failed!\n");
        return -1;
    }
    timer_loop();
    return 0;
}

