/*
 * =====================================================================================
 *
 *       Filename:  config.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 14时41分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "config.h"

#define GET_DEFAULT_VALUE(s, def) if ((s)==0) {s=(def);}

struct eye_config g_config;

static gboolean verbose = FALSE;

static GOptionEntry entries[] =
{
    { "interval", 'i', 0, G_OPTION_ARG_INT, &g_config.interval, "Interval of every rest, set to I second", "I" },
    { "idle-time", 'd', 0, G_OPTION_ARG_INT, &g_config.max_idle_time, "Idle for D second(no keyboard event and no mouse event), reset the interval", "D" },
    { "rest-time", 'r', 0, G_OPTION_ARG_INT, &g_config.rest_time, "Rest time", "R"},
    { "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Be verbose", NULL },
    { NULL }
};

static void config_from_argv(int argc, char** argv)
{
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new (NULL);
    g_option_context_add_main_entries (context, entries, NULL);
    if (!g_option_context_parse (context, &argc, &argv, &error))
    {
        g_print ("option parsing failed: %s\n", error->message);
        exit (-1);
    }

    g_option_context_free(context);
}

static void config_from_file()
{
    const gchar* user_config = g_get_user_config_dir();

    GString* path = g_string_new (user_config);
    g_string_append(path, "/eyerest.conf");

    g_message("Load config file: %s", path->str);

    GKeyFile* key_file = g_key_file_new();

    if(g_key_file_load_from_file (key_file, path->str, G_KEY_FILE_NONE, NULL))
    {
        GET_DEFAULT_VALUE(g_config.interval,        g_key_file_get_integer (key_file, "Config", "interval", NULL));
        GET_DEFAULT_VALUE(g_config.rest_time,       g_key_file_get_integer (key_file, "Config", "rest_time", NULL));
        GET_DEFAULT_VALUE(g_config.max_idle_time,   g_key_file_get_integer (key_file, "Config", "max_idle_time", NULL));
    }
    
    g_key_file_free(key_file);
    g_string_free(path, TRUE);
}

static void config_set_default()
{
    GET_DEFAULT_VALUE(g_config.interval,       45*60);
    GET_DEFAULT_VALUE(g_config.rest_time,      3*60);
    GET_DEFAULT_VALUE(g_config.max_idle_time,  5*60);
}

gboolean config_init(int argc, char* argv[])
{
    memset(&g_config, 0, sizeof(g_config));

    config_from_argv(argc, argv);

    config_from_file();

    config_set_default();

    g_print("interval = %d\nrest_time= %d\nmax_idle_time = %d\n", g_config.interval, g_config.rest_time, g_config.max_idle_time);
    return TRUE;
}
