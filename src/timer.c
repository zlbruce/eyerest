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
#include <event.h>

#include "timer.h"
#include "state.h"

#define TIMER 1

const struct timeval timeout = {TIMER, 0};

static struct event_base* s_base = NULL;
static struct event* s_timer;


static void timer_callback(int fd, short event, void* ctx)
{
    state_timeout_cb(TIMER);
    evtimer_add(s_timer, &timeout);
}

gboolean timer_init()
{
    s_base = event_base_new();
    
    s_timer = evtimer_new(s_base, timer_callback, NULL);
    evtimer_add(s_timer, &timeout);

    return TRUE;
}

void timer_loop()
{
    event_base_dispatch(s_base);
}
