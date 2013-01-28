/*
 * =====================================================================================
 *
 *       Filename:  dbus_eyerest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年01月28日 09时42分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */


#include <E_DBus.h>
#include "dbus_eyerest.h"

static E_DBus_Connection* s_dbus_connection = NULL;

static char* s_dbus_eyerest_name = "org.zlbruce.eyerest";
static char* s_dbus_eyerest_object = "/";
static char* s_dbus_eyerest_interface = "org.zlbruce.eyerest.basic";

static eyerest_state_cb s_eyerest_cb = NULL;
static void* s_eyerest_cb_ctx = NULL;
static E_DBus_Signal_Handler* s_eyerest_signal_handler = NULL;

static void _dbus_status_signal_cb (void *data, DBusMessage *msg)
{
    if(!s_eyerest_cb)
    {
        return;
    }

    DBusMessageIter iter;
    if (!dbus_message_iter_init(msg, &iter))
    {
        // TODO: Log
        return;
    }

    uint32_t time_remain;
    char* state = NULL;
    // get time-remain
    if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&iter))
    {
        // TODO: Log
        return;
    }
    dbus_message_iter_get_basic(&iter, &time_remain);

    // get state
    dbus_message_iter_next(&iter);
    if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&iter))
    {
        // TODO: Log
        return;
    }
    dbus_message_iter_get_basic(&iter, &state);

    s_eyerest_cb(time_remain, state, s_eyerest_cb_ctx);
}

int eyerest_dbus_init(eyerest_state_cb cb, void* ctx)
{
    //e_dbus_init();

    s_dbus_connection = e_dbus_bus_get(DBUS_BUS_SESSION);

    s_eyerest_signal_handler = e_dbus_signal_handler_add(s_dbus_connection, 
            s_dbus_eyerest_name,
            s_dbus_eyerest_object,
            s_dbus_eyerest_interface,
            "status",
            _dbus_status_signal_cb,
            NULL);

    s_eyerest_cb = cb;
    s_eyerest_cb_ctx = ctx;

    return 0;
}

int eyerest_dbus_shutdown()
{
    s_eyerest_cb = NULL;
    s_eyerest_cb_ctx = NULL;
    e_dbus_signal_handler_del(s_dbus_connection, s_eyerest_signal_handler);
    //e_dbus_shutdown();

    return 0;
}

void eyerest_dbus_pause()
{
    DBusMessage* msg;

    msg = dbus_message_new_method_call(s_dbus_eyerest_name, // target for the method call
            s_dbus_eyerest_object, // object to call on
            s_dbus_eyerest_interface, // interface to call on
            "pause"); // method name
    if (NULL == msg) { 
        return;
    }

    e_dbus_message_send(s_dbus_connection, msg, NULL, 1000, NULL);

    dbus_message_unref(msg);
}

void eyerest_dbus_unpause()
{
    DBusMessage* msg;

    msg = dbus_message_new_method_call(s_dbus_eyerest_name, // target for the method call
            s_dbus_eyerest_object, // object to call on
            s_dbus_eyerest_interface, // interface to call on
            "unpause"); // method name
    if (NULL == msg) { 
        return;
    }

    e_dbus_message_send(s_dbus_connection, msg, NULL, 1000, NULL);

    dbus_message_unref(msg);
}
void eyerest_dbus_rest_now()
{
    DBusMessage* msg;

    msg = dbus_message_new_method_call(s_dbus_eyerest_name, // target for the method call
            s_dbus_eyerest_object, // object to call on
            s_dbus_eyerest_interface, // interface to call on
            "rest_now"); // method name
    if (NULL == msg) { 
        return;
    }

    e_dbus_message_send(s_dbus_connection, msg, NULL, 1000, NULL);

    dbus_message_unref(msg);
}
void eyerest_dbus_delay(uint32_t t)
{
    DBusMessage* msg;
    DBusMessageIter args;


    msg = dbus_message_new_method_call(s_dbus_eyerest_name, // target for the method call
            s_dbus_eyerest_object, // object to call on
            s_dbus_eyerest_interface, // interface to call on
            "delay"); // method name
    if (NULL == msg) { 
        return;
    }

    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &t))
    {
        return;
    }

    e_dbus_message_send(s_dbus_connection, msg, NULL, 1000, NULL);

    dbus_message_unref(msg);
}
