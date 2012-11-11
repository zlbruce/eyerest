const Gio = imports.gi.Gio;

const eyerest_interface = <interface name="org.zlbruce.eyerest.basic">
    <method name="delay">
        <arg name="time" type="u" direction="in"/>
    </method>
    <method name="pause">
    </method>
    <method name="unpause">
    </method>
    <method name="rest_now">
    </method>
    <method name="get_time_remain">
        <arg name="time" type="u" direction="out"/>
    </method>
    <method name="get_state">
        <arg name="state" type="s" direction="out"/>
    </method>
    <signal name="status">
        <arg name="time_remain" type="u" />
        <arg name="state" type="s" />
    </signal>
</interface>;

const eyerest_proxy = Gio.DBusProxy.makeProxyWrapper(eyerest_interface);

function eyerest_dbus() {
    return new eyerest_proxy(Gio.DBus.session, 'org.zlbruce.eyerest',
            '/');
}

