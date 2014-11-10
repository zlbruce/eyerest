/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 11时23分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <glib.h>

#include "timer.h"
#include "state.h"
#include "notify.h"

#define TIMER 1

static GMainLoop* s_loop = NULL;


static gboolean timer_callback(gpointer data)
{
    state_timeout_cb(TIMER);
    notify_timeout_cb(TIMER);
    return TRUE;
}

gboolean timer_init()
{
    s_loop = g_main_loop_new ( NULL , FALSE );

    g_timeout_add_seconds (TIMER, timer_callback, NULL);

    return TRUE;
}

void timer_loop()
{
    g_main_loop_run (s_loop);
    g_main_loop_unref(s_loop);
}
