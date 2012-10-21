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

#include "xevent.h"
#include "timer.h"
#include "config.h"
#include "eye_log.h"
#include "xlock.h"

#define TIMER 1
#define MAX_IDLE_TIME 60

const struct timeval timeout = {TIMER, 0};

static struct event_base* s_base = NULL;
static struct event* s_xevent_timer;
static struct event* s_timerest_timer;
static struct event* s_xlock_timer;;

static unsigned int s_rest_time = 0;

static int s_flag_run = 0;

void timer_stop_rest_dec()
{
    s_flag_run = 0;
}

void timer_start_rest_dec()
{
    s_flag_run = 1;
}

void timer_reset_rest()
{
    s_rest_time = g_config.interval;
}

static void set_lock_timer()
{
    struct timeval timeout;
    timeout.tv_sec = g_config.rest_time;
    timeout.tv_usec = 0;

    evtimer_add(s_xlock_timer, &timeout);
}

static void xlock_callback(int fd, short event, void* ctx)
{
    // unlock
    xlock_unlockscreen();

    timer_reset_rest();
    timer_start_rest_dec();
}

static void timerest_callback(int fd, short event, void* ctx)
{
    if(s_rest_time == 0)
    {
        // TODO: have a rest
        timer_reset_rest();
        xlock_lockscreen();
        set_lock_timer();
    }

    if(s_flag_run)
    {
        s_rest_time -= TIMER;
    }

    eye_debug("rest_time = %d\n", s_rest_time);

    evtimer_add(s_timerest_timer, &timeout);
}

static void xevent_callback(int fd, short event, void* ctx)
{
    static unsigned int s_idle_time = 0;
    if(!xevent_has_event())
    {
        s_idle_time += TIMER;
    }
    else
    {
        s_idle_time = 0;
        timer_start_rest_dec();
    }

    if(s_idle_time >= g_config.max_idle_time)
    {
        timer_stop_rest_dec();
    }

    xevent_clear_event();

    evtimer_add(s_xevent_timer, &timeout);
}

int timer_init()
{
    s_base = event_base_new();
    
    s_xevent_timer = evtimer_new(s_base, xevent_callback, NULL);
    evtimer_add(s_xevent_timer, &timeout);

    s_timerest_timer = evtimer_new(s_base, timerest_callback, NULL);
    evtimer_add(s_timerest_timer, &timeout);

    s_xlock_timer = evtimer_new(s_base, xlock_callback, NULL);

    timer_reset_rest();
    timer_start_rest_dec();
}

void timer_loop()
{
    event_base_dispatch(s_base);
}
