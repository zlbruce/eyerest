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

static gint interval = 2700;
static gint idle_time = 300;
static gint rest_time = 180;
static gboolean verbose = FALSE;

static GOptionEntry entries[] =
{
    { "interval", 'i', 0, G_OPTION_ARG_INT, &interval, "Interval of every rest, set to I second", "I" },
    { "idle-time", 'd', 0, G_OPTION_ARG_INT, &idle_time, "Idle for D second(no keyboard event and no mouse event), reset the interval", "D" },
    { "rest-time", 'r', 0, G_OPTION_ARG_INT, &rest_time, "Rest time", "R"},
    { "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Be verbose", NULL },
    { NULL }
};


int main(int argc, char* argv[]) 
{
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new (NULL);
    g_option_context_add_main_entries (context, entries, NULL);
    if (!g_option_context_parse (context, &argc, &argv, &error))
    {
        g_print ("option parsing failed: %s\n", error->message);
        exit (1);
    }

    if (config_init() < 0)
    {
        g_error("config_init failed!\n");
        return -1;
    }

    if (xevent_init() < 0)
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

