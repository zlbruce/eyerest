/*
 * =====================================================================================
 *
 *       Filename:  eyerest-cli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月04日 23时39分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#include <glib.h>

#include "eyerest-dbus.h"

static gboolean s_status = FALSE;
static guint s_delay_time = 0;
static gboolean s_pause = FALSE;
static gboolean s_continue = FALSE;
static gboolean s_rest_now = FALSE;

static GOptionEntry entries[] =
{
    { "status", 's', 0, G_OPTION_ARG_NONE, &s_status, "Print the status", NULL },
    { "delay", 'd', 0, G_OPTION_ARG_INT, &s_delay_time, "Delay the rest", "T"},
    { "pause", 'p', 0, G_OPTION_ARG_NONE, &s_pause, "Pause counter", NULL},
    { "continue", 'c', 0, G_OPTION_ARG_NONE, &s_continue, "Continue counter", NULL},
    { "rest-now", 'r', 0, G_OPTION_ARG_NONE, &s_rest_now, "Rest now", NULL},
    { NULL }
};

static void process_request(OrgZlbruceEyerestBasic* proxy)
{
    GError *error = NULL;
    if(s_status)
    {
        guint out_time = 0;
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_get_time_remain_sync (
                    proxy,
                    &out_time,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed get_time_remain failed: %s\n", error->message);
            return;
        }

        gchar* st = NULL;
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_get_state_sync (
                    proxy,
                    &st,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed get_state failed: %s\n", error->message);
            return;
        }

        g_print("time remain: %u\n", out_time);
        g_print("state:       %s\n", st);
    }

    if(s_delay_time != 0)
    {
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_delay_sync (
                    proxy,
                    s_delay_time,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed delay failed: %s\n", error->message);
            return;
        }
    }

    if(s_pause)
    {
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_pause_sync (
                    proxy,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed pause failed: %s\n", error->message);
            return;
        }
    }

    if(s_continue)
    {
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_continue_sync (
                    proxy,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed continue failed: %s\n", error->message);
            return;
        }
    }

    if(s_rest_now)
    {
        error = NULL;
        if (!org_zlbruce_eyerest_basic_call_rest_now_sync (
                    proxy,
                    NULL,
                    &error))
        {
            g_print ("call dbus methed rest_now failed: %s\n", error->message);
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    GError *error = NULL;
    GOptionContext *context;

    g_type_init();

    context = g_option_context_new (NULL);
    g_option_context_add_main_entries (context, entries, NULL);
    if (!g_option_context_parse (context, &argc, &argv, &error))
    {
        g_print ("option parsing failed: %s\n", error->message);
        return (-1);
    }

    g_option_context_free(context);

    OrgZlbruceEyerestBasic* proxy;
    error = NULL;

    proxy = org_zlbruce_eyerest_basic_proxy_new_for_bus_sync(
            G_BUS_TYPE_SESSION,
            G_DBUS_PROXY_FLAGS_NONE,
            "org.zlbruce.eyerest",
            "/",
            NULL,
            &error);
    if(proxy == NULL)
    {
        g_print ("init dbus failed: %s\n", error->message);
        return -1;
    }

    process_request(proxy);

    g_object_unref (proxy);
    return 0;
}
