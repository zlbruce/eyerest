/*
 * =====================================================================================
 *
 *       Filename:  xevent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 10时28分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#include <X11/Xlib.h>
#include <X11/extensions/record.h>
#include <stdio.h>
#include <stdlib.h>     /* getenv(), etc. */
#include <pthread.h>

#include "eye_log.h"

Display* s_display = NULL;
XRecordContext s_context;
int s_has_event = 0;

// 判断当前是否有鼠标键盘事件
int xevent_has_event()
{
    return s_has_event;
}

// 清除所有事件
void xevent_clear_event()
{
    s_has_event = 0;
}

// 初始化
int xevent_init()
{
    s_display = XOpenDisplay(getenv("DISPLAY"));
    if (s_display == NULL) {
        eye_error("cannot connect to X server '%s'\n", getenv("DISPLAY"));
        return -1;
    }


    XRecordClientSpec clients = XRecordAllClients;
    XRecordRange* range = XRecordAllocRange();
    if (range == 0) {
        eye_error("unable to allocate XRecordRange\n");
        return -1;
    }

    range->device_events.first = KeyPress;
    range->device_events.last = MotionNotify;
    s_context = XRecordCreateContext (s_display, 0, &clients, 1, &range, 1);
    if (s_context == 0) {
        eye_error("unable to create XRecordContext\n");
        exit(-1);
    }

    XFree(range);

    return 0;
}

static void xevent_event_callback(XPointer p, XRecordInterceptData* data)
{
    s_has_event = 1;
}

static void* xevent_thread_fuc(void* ctx)
{
    // 会一直阻塞在这里
    XRecordEnableContext(s_display, s_context, xevent_event_callback, 0);

    XRecordFreeContext(s_display, s_context);
    XCloseDisplay(s_display);

    return NULL;
}
// 运行监听线程
void xevent_run()
{
    pthread_t thread;
    pthread_create(&thread, NULL, xevent_thread_fuc, NULL);
}

// 停止监听线程
void xevent_stop()
{
    // TODO
}
