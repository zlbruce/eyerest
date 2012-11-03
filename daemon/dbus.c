/*
 * =====================================================================================
 *
 *       Filename:  dbus.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月03日 01时17分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */

#include "dbus.h"
#include "state.h"

static OrgZlbruceEyerestBasic* interface = NULL;

static gboolean on_handle_delay (
        OrgZlbruceEyerestBasic *object,
        GDBusMethodInvocation *invocation,
        guint arg_time)
{
    g_message("delay %d seconds", arg_time);

    state_active_delay(arg_time);

    org_zlbruce_eyerest_basic_complete_delay(object, invocation);

    return TRUE;
}

static gboolean on_handle_get_time_remain (
        OrgZlbruceEyerestBasic *object,
        GDBusMethodInvocation *invocation)
{
    guint time = state_active_get_time_remain();
    org_zlbruce_eyerest_basic_complete_get_time_remain(object, invocation, time);

    return TRUE;
}

static gboolean on_handle_pause (
        OrgZlbruceEyerestBasic *object,
        GDBusMethodInvocation *invocation)
{
    state_active_pause();
    org_zlbruce_eyerest_basic_complete_pause(object, invocation);

    return TRUE;
}

static gboolean on_handle_continue (
        OrgZlbruceEyerestBasic *object,
        GDBusMethodInvocation *invocation)
{
    state_active_continue();
    org_zlbruce_eyerest_basic_complete_continue(object, invocation);

    return TRUE;
}

static void on_bus_acquired (GDBusConnection *connection,
        const gchar     *name,
        gpointer         user_data)
{
    /* This is where we'd export some objects on the bus */
    interface = org_zlbruce_eyerest_basic_skeleton_new ();
    g_signal_connect (interface,
            "handle-delay",
            G_CALLBACK (on_handle_delay),
            NULL);
    g_signal_connect (interface,
            "handle-get-time-remain",
            G_CALLBACK (on_handle_get_time_remain),
            NULL);
    g_signal_connect (interface,
            "handle-pause",
            G_CALLBACK (on_handle_pause),
            NULL);
    g_signal_connect (interface,
            "handle-continue",
            G_CALLBACK (on_handle_continue),
            NULL);

    GError *error = NULL;
    if (!g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (interface),
            connection,
            "/",
            &error))
    {
        g_warning("g_dbus_interface_skeleton_export failed: %s", error->message);
    }
}

static void on_name_acquired (GDBusConnection *connection,
        const gchar     *name,
        gpointer         user_data)
{
    g_print ("Acquired the name %s on the session bus\n", name);
}

static void on_name_lost (GDBusConnection *connection,
        const gchar     *name,
        gpointer         user_data)
{
    g_print ("Lost the name %s on the session bus\n", name);
}

gboolean dbus_init()
{
    guint owner_id = 0;

    owner_id =  g_bus_own_name (G_BUS_TYPE_SESSION,
            "org.zlbruce.eyerest",
            G_BUS_NAME_OWNER_FLAGS_NONE,
            on_bus_acquired,
            on_name_acquired,
            on_name_lost,
            NULL,
            NULL);
    
    return TRUE;
}

void dbus_sent_status(guint time_remain)
{
    g_assert(interface);
    org_zlbruce_eyerest_basic_emit_status (interface, time_remain);
}
