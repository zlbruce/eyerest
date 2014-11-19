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
#define GET_DEFAULT_VALUE_CPYSTR(s, def) if ((s)==0) {s = g_malloc(PATH_MAX);g_stpcpy(s, def);}
#define SET_DEFAULT_VALUE_CPYSTR(s, def) if ((def)!=0) {GET_DEFAULT_VALUE_CPYSTR(s, def)};
struct eye_config g_config;

static GOptionEntry entries[] =
{
    { "interval", 'i', 0, G_OPTION_ARG_INT, &g_config.interval, "Interval of every rest", "T" },
    { "idle-time", 'd', 0, G_OPTION_ARG_INT, &g_config.max_idle_time, "Idle time", "T" },
    { "rest-time", 'r', 0, G_OPTION_ARG_INT, &g_config.rest_time, "Rest time", "T"},
    { "font", 'f', 0, G_OPTION_ARG_STRING, &g_config.font, "Display font", "Monospace:size=28"},
    { "color", 'c', 0, G_OPTION_ARG_STRING, &g_config.color, "Display color", "red"},
    { "x-coordinate", 'x', 0, G_OPTION_ARG_INT, &g_config.x_coordinate, "X-coordinate (percent)", "50"},
    { "y-coordinate", 'y', 0, G_OPTION_ARG_INT, &g_config.y_coordinate, "Y-coordinate (percent)", "50"},
    { "format", 'F', 0, G_OPTION_ARG_STRING, &g_config.format, "Display format", "FORMAT"},
    { "foreground", 'g', 0, G_OPTION_ARG_NONE, &g_config.foreground, "Run in foreground, do not detach from the console.", NULL },
    { "notify-time", '\0', 0, G_OPTION_ARG_INT, &g_config.notify_time, "Notify time (second)", "60"},
    { "notify-format", '\0', 0, G_OPTION_ARG_STRING, &g_config.notify_format, "Nodify Text Format", "%M-%S"},
    { "notify-action", '\0', 0, G_OPTION_ARG_INT, &g_config.notify_action, "Send Notify Action(1) or Not(0)", "0"},
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
        GError *error;
        gchar* font   = g_key_file_get_locale_string(key_file, "Display", "font",   NULL, NULL);
        gchar* color  = g_key_file_get_locale_string(key_file, "Display", "color",  NULL, NULL);
        gchar* format = g_key_file_get_locale_string(key_file, "Display", "format", NULL, &error);
        if(format == NULL)
        {
            g_print ("get format failed: %s\n", error->message);
        }
        SET_DEFAULT_VALUE_CPYSTR(g_config.font, font);
        SET_DEFAULT_VALUE_CPYSTR(g_config.color, color);
        SET_DEFAULT_VALUE_CPYSTR(g_config.format, format);
        g_free(font);
        g_free(color);
        g_free(format);

        GET_DEFAULT_VALUE(g_config.x_coordinate,   g_key_file_get_integer (key_file, "Display", "x-coordinate", NULL));
        GET_DEFAULT_VALUE(g_config.y_coordinate,   g_key_file_get_integer (key_file, "Display", "y-coordinate", NULL));

        gchar* notify_name = g_key_file_get_locale_string(key_file, "Notify", "format", NULL, NULL);
        SET_DEFAULT_VALUE_CPYSTR(g_config.notify_format, notify_name);
        g_free(notify_name);

        GET_DEFAULT_VALUE(g_config.notify_time,   g_key_file_get_integer (key_file, "Notify", "time", NULL));
        GET_DEFAULT_VALUE(g_config.notify_action, g_key_file_get_integer (key_file, "Notify", "action", NULL));

    }

    g_key_file_free(key_file);
    g_string_free(path, TRUE);
}

static void config_set_default()
{
    GET_DEFAULT_VALUE(g_config.interval,       45*60);
    GET_DEFAULT_VALUE(g_config.rest_time,      3*60);
    GET_DEFAULT_VALUE(g_config.max_idle_time,  5*60);

    GET_DEFAULT_VALUE_CPYSTR(g_config.font,   "Monospace:size=28");
    GET_DEFAULT_VALUE_CPYSTR(g_config.color,  "red");
    GET_DEFAULT_VALUE_CPYSTR(g_config.format, "%M:%S");

    GET_DEFAULT_VALUE(g_config.x_coordinate,   50);
    GET_DEFAULT_VALUE(g_config.y_coordinate,   50);

    GET_DEFAULT_VALUE_CPYSTR(g_config.notify_format, "%M:%S");
    GET_DEFAULT_VALUE(g_config.notify_time,          60);
    GET_DEFAULT_VALUE(g_config.notify_action,        0);
}

gboolean config_init(int argc, char* argv[])
{
    memset(&g_config, 0, sizeof(g_config));

    config_from_argv(argc, argv);

    config_from_file();

    config_set_default();

    g_message("interval = %d", g_config.interval);
    g_message("rest_time = %d", g_config.rest_time);
    g_message("max_idle_time = %d", g_config.max_idle_time);
    g_message("font = %s", g_config.font);
    g_message("color = %s", g_config.color);
    g_message("format = %s", g_config.format);
    g_message("x = %d", g_config.x_coordinate);
    g_message("y = %d", g_config.y_coordinate);
    g_message("notify_format = %s", g_config.notify_format);
    g_message("notify_time = %d", g_config.notify_time);
    g_message("notify_action = %d", g_config.notify_action);

    return TRUE;
}
