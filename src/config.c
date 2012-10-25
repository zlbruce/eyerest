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
#include "eye_log.h"

struct eye_config g_config;

static int conf_to_printf_cb(void* ctx, const char* key, const char* val)
{
#define INI_GET(a, b)     \
    if (0 == strcmp(key, b)) { \
        g_config.a  = atoi(val); \
    }

    INI_GET(interval,            "[Config]interval");
    INI_GET(rest_time,           "[Config]rest_time");
    INI_GET(max_idle_time,       "[Config]max_idle_time");

#undef INI_GET

    return 0;
}

static char* str_trimn_ex(char* str, const char* delim)
{
    char* p1 = str;
    char* p2 = 0;
    int len;

    if (str == 0 || str[0] == 0)
    {
        return str;
    }
    while (*p1 && strchr(delim, *p1))
    {
        p1++;
    }
    if (*p1 == 0)
    {
        return p1;
    }

    len = strlen(p1);
    p2 = p1 + len - 1;
    while (strchr(delim, *p2))
    {
        p2--;
    }

    *(p2 + 1) = 0;
    return p1;
}

/**
 * 裁剪掉前后的"\r\n\t "，no move
 * @remark 返回的指针>=buf
 */
static char* str_trimn(char* buf)
{
    return str_trimn_ex(buf, "\r\n\t ");
}

static int conf_file_parse(const char* fname, void* ctx, int (* callback)(void* ctx, const char* key, const char* val))
{
    FILE* file = 0;
    char buff[1024] = {0};
    char* line = 0;
    char key[256 + 256 + 4] = {0};
    //char val[1024] = {0};
    int ksize = 0;
    int lsize = 0;
    char* pos = 0;

    file = fopen(fname, "r+");
    if (!file)
    {
        return 0;
    }

    while (!feof(file))
    {
        //read line and trim
        if (0 == fgets(buff, sizeof(buff) - 1, file))
        {
            break;
        }
        line = str_trimn(buff);
        lsize = strlen(line);

        //note
        if (line[0] == 0 || line[0] == '#' || line[0] == ';' || (line[0] == '/' && line[1] == '/'))
        {
            continue;
        }

        //get section
        if (line[0] == '[' && line[lsize - 1] == ']')
        {
            strcpy(key, line);
            ksize = lsize;
            continue;
        }

        //split
        pos = strchr(line, '=');
        if (pos)
        {
            char* first = 0;
            char* second = 0;

            *pos = 0; // split
            first = str_trimn(line);
            second = str_trimn(pos + 1);

            strcpy(&key[ksize], first);
            if (callback)
                if (0 != callback(ctx, key, second))
                {
                    break;
                }
        }
    }

    if (file)
    {
        fclose(file);
    }
    return 0;
}

int check_and_create_dir(char* path)
{
    int dir = open(path, O_DIRECTORY);
    if(dir >= 0)
    {
        close(dir);
        return 0;
    }

    return mkdir(path, 0700);
}

gboolean config_init()
{
    char config_path[PATH_MAX] = {0};
    char* home = getenv("HOME");
    if(home == NULL)
    {
        return FALSE;
    }
    printf("home = %s\n", home);

    strcat(config_path, home);
    strcat(config_path, "/.config");

    if (check_and_create_dir(config_path) < 0)
    {
        printf("check_and_create_dir failed\n");
        return FALSE;
    }

    strcat(config_path, "/eyerest.conf");

    if (0 != conf_file_parse(config_path, NULL, conf_to_printf_cb))
    {
        printf("conf_file_parse failed\n");
        return FALSE;
    }
#define GET_DEFAULT_VALUE(s, def) if ((s)==0) {s=def;}
    GET_DEFAULT_VALUE(g_config.interval,       45*60);
    GET_DEFAULT_VALUE(g_config.rest_time,      3*60);
    GET_DEFAULT_VALUE(g_config.max_idle_time,  5*60);
#undef GET_DEFAULT_VALUE

    eye_debug("interval = %d\nrest_time= %d\nmax_idle_time = %d\n", g_config.interval, g_config.rest_time, g_config.max_idle_time);
    return TRUE;
}

gboolean config_reinit(struct eye_config* config)
{
    // TODO
    return TRUE;
}

gboolean config_write(struct eye_config* config)
{
    // TODO
    return TRUE;
}
