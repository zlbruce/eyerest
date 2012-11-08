const Gtk = imports.gi.Gtk;

const Gettext = imports.gettext.domain('gnome-shell-extensions-eyerest');
const _ = Gettext.gettext;

const Me = imports.misc.extensionUtils.getCurrentExtension();
const Util = Me.imports.util;

let settings;
let settings_string;
let settings_int;

function init() {
    Util.initTranslations(Me);
    settings = Util.getSettings(Me);
    settings_string = {
        formatstring: {label: _("Display format in the panel menu")},
    };
    settings_int = {
        notifytime: {label: _("Notify time before lock the screen"),
                     min: 10, max: 300, step: 1, default: 60},
    };
}

function createStringSetting(setting)
{
    let hbox = new Gtk.Box({ orientation: Gtk.Orientation.HORIZONTAL });

    let setting_label = new Gtk.Label({ label: settings_string[setting].label,
                                        xalign: 0 });

    let setting_entry = new Gtk.Entry();
    
    setting_entry.set_text(settings.get_string(setting));
    setting_entry.set_size_request(200, -1);
    setting_entry.connect('focus_out_event', function(self) 
    {
        settings.set_string(setting, self.get_text());
        //global.logError("your type is " + self.get_text());
        return false;
    });

    if (settings_string[setting].help) {
        setting_label.set_tooltip_text(settings_string[setting].help)
        setting_entry.set_tooltip_text(settings_string[setting].help)
    }

    hbox.pack_start(setting_label, true, true, 0);
    hbox.add(setting_entry);

    return hbox;
}

function createIntSetting(setting)
{
    let hbox = new Gtk.Box({ orientation: Gtk.Orientation.HORIZONTAL });

    let setting_label = new Gtk.Label({ label: settings_int[setting].label,
                                        xalign: 0 });

    let setting_entry = new Gtk.SpinButton.new_with_range (settings_int[setting].min,
                                                           settings_int[setting].max,
                                                           settings_int[setting].step);
    
    setting_entry.set_value(settings.get_int(setting));
    setting_entry.set_size_request(200, -1);
    setting_entry.connect('value-changed', function(self) 
    {
        settings.set_int(setting, self.get_value());
        //global.logError("your type is " + self.get_text());
        return false;
    });

    if (settings_int[setting].help) {
        setting_label.set_tooltip_text(settings_int[setting].help)
        setting_entry.set_tooltip_text(settings_int[setting].help)
    }

    hbox.pack_start(setting_label, true, true, 0);
    hbox.add(setting_entry);

    return hbox;
}

function buildPrefsWidget() 
{
    let frame = new Gtk.Box({ orientation: Gtk.Orientation.VERTICAL,
                              border_width: 10 });
    let vbox = new Gtk.Box({ orientation: Gtk.Orientation.VERTICAL,
                             margin: 20, margin_top: 10 });

    for (setting in settings_string)
    {
        let hbox = createStringSetting(setting);
        vbox.add(hbox);
    }
    for (setting in settings_int)
    {
        let hbox = createIntSetting(setting);
        vbox.add(hbox);
    }

    frame.add(vbox);
    frame.show_all();
    return frame;
}

