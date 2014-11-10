/*
 * =====================================================================================
 *
 *       Filename:  notify.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年11月14日 17时32分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhanglei (zhanglei), zhangleibruce@gmail.com
 *        Company:  zlb.me
 *
 * =====================================================================================
 */
#include <gio/gio.h>

#include "notify.h"
#include "state.h"
#include "config.h"

static GDBusProxy* notify_proxy = NULL;
static guint s_notify_id = 0;
static gboolean s_notified = TRUE;

static void on_notify_signal (GDBusProxy *proxy,
        gchar      *sender_name,
        gchar      *signal_name,
        GVariant   *parameters,
        gpointer    user_data)
{
    guint32 notify_id;
    guint32 reason;
    gchar* action;

    if(g_strcmp0(signal_name, "NotificationClosed") == 0)
    {
        g_return_if_fail(g_variant_is_of_type (parameters, G_VARIANT_TYPE ("(uu)")));

        g_variant_get(parameters, "(uu)", &notify_id, &reason);
        g_print("notify_id = %u, reason = %u\n", notify_id, reason);

        if(notify_id == s_notify_id)
        {
            s_notify_id = 0;
            s_notified = TRUE;
        }
    }
    else if(g_strcmp0(signal_name, "ActionInvoked") == 0)
    {
        g_return_if_fail(g_variant_is_of_type (parameters, G_VARIANT_TYPE ("(us)")));

        g_variant_get(parameters, "(us)", &notify_id, &action);
        g_print("notify_id = %u, action = %s\n", notify_id, action);

        if(notify_id == s_notify_id)
        {
            if(g_strcmp0(action, "2") == 0)
            {
                state_active_delay(180);
            }
        }
    }
}

gboolean notify_init()
{
    GDBusProxy* notify_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
            G_DBUS_PROXY_FLAGS_NONE,
            NULL,
            "org.freedesktop.Notifications",
            "/org/freedesktop/Notifications",
            "org.freedesktop.Notifications",
            NULL,
            NULL);

    if(notify_proxy == NULL)
    {
        return FALSE;
    }

/*
    g_signal_connect (G_OBJECT(notify_proxy),
            "NotificationClosed",
            G_CALLBACK (on_notify_closed),
            NULL);

    g_signal_connect (G_OBJECT(notify_proxy),
            "ActionInvoked",
            G_CALLBACK (on_notify_action_invoked),
            NULL);
            */

    g_signal_connect (G_OBJECT(notify_proxy),
            "g-signal",
            G_CALLBACK (on_notify_signal),
            NULL);

    return TRUE;
}

static void notify_send(gchar* text, gint time_remain)
{
    GVariantBuilder actions;
    GVariantBuilder hints;

    g_variant_builder_init (&actions, G_VARIANT_TYPE ("as"));

    if (g_config.notify_action)
    {
        g_variant_builder_add(&actions, "s", "1");
        g_variant_builder_add(&actions, "s", "I kown");
        g_variant_builder_add(&actions, "s", "2");
        g_variant_builder_add(&actions, "s", "Delay 3 min");
    }

    g_variant_builder_init (&hints, G_VARIANT_TYPE ("a{sv}"));

    GVariant* result = g_dbus_proxy_call_sync(notify_proxy,
            "Notify",
            g_variant_new("(susssasa{sv}i)",
                "eyerestray",
                s_notify_id,
                "dialog-information",
                "It's time for a break",
                text,
                &actions,
                &hints,
                time_remain * 1000),
            G_DBUS_CALL_FLAGS_NONE,
            -1,
            NULL,
            NULL);

    if(result != NULL)
    {
        g_variant_get (result, "(u)", &s_notify_id);
        g_print("s_notify_id = %u\n", s_notify_id);
        g_variant_unref (result);
    }
}

static void notify_close()
{
    if(notify_proxy == NULL || s_notify_id == 0)
    {
        return;
    }

    g_dbus_proxy_call_sync(notify_proxy,
            "CloseNotification",
            g_variant_new("(u)",
                s_notify_id),
            G_DBUS_CALL_FLAGS_NONE,
            -1,
            NULL,
            NULL);
}


void notify_timeout_cb(guint time)
{
    time_t t = state_active_get_time_remain();

    if (t < g_config.notify_time && t > 0)
    {
        if(!s_notified)
        {
            static gchar time_str[PATH_MAX];
            struct tm* tm = localtime(&t);
            if(tm == NULL)
            {
                g_snprintf(time_str, sizeof(time_str), "%lu", (unsigned long)t);
            }
            else
            {
                strftime(time_str, sizeof(time_str), g_config.notify_format, tm);
            }

            notify_send(time_str, t);
        }
    }
    else
    {
        s_notified = TRUE;
        notify_close();
    }
}
