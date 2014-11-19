
#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xfullscreen.h"

static Display* s_dpy = NULL;

gboolean xfullscreen_init()
{
    s_dpy = XOpenDisplay(getenv("DISPLAY"));
    if (s_dpy == NULL) {
        g_critical("cannot connect to X server '%s'\n", getenv("DISPLAY"));
        return FALSE;
    }

    return TRUE;
}

static Window get_active_window(Display* dpy,Window root)
{
    Atom active_atom = XInternAtom(dpy, "_NET_ACTIVE_WINDOW" , True);
    Atom actual;

    int format;
    unsigned long num, bytes_after;
    Window *w = 0;
    int status = XGetWindowProperty(dpy,
                                root,
                                active_atom,
                                0L,
                                (~0L),
                                False,
                                AnyPropertyType,
                                &actual,
                                &format,
                                &num,
                                &bytes_after,
                                (unsigned char**)&w);
    if (status >= Success && num)
    {
        Window ret = w[0];
        XFree(w);

        return ret;
    }

    return 0;
}

static gboolean is_fullscreen(Display* dpy,Window w)
{
    Atom state = XInternAtom(dpy, "_NET_WM_STATE", True);
    Atom fullscreen = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", True);
    Atom actual;

    int format;
    unsigned long num, bytes_after;
    Atom *atom;

    int status = XGetWindowProperty(dpy,
                          w,
                          state,
                          0L,
                          (~0L),
                          False,
                          AnyPropertyType,
                          &actual,
                          &format,
                          &num,
                          &bytes_after,
                          (unsigned char**)&atom);

    if(status >= Success && num)
    {
        int i;
        for (i = 0; i < num; i++)
        {
            if (fullscreen == atom[i])
            {
                printf("is fullscreen\n");
                return TRUE;
            }
        }

        XFree(atom);
    }

    return FALSE;
}

gboolean xfullscreen_has_fullscreen()
{
    int nscreens = ScreenCount(s_dpy);

    int i;
    for(i = 0; i < nscreens; i++)
    {
        Window root = RootWindow(s_dpy, i);
        Window w = get_active_window(s_dpy, root);
        if (is_fullscreen(s_dpy, w))
        {
            return TRUE;
        }
    }

    return FALSE;
}
