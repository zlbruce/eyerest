// Here we avoid loading the header multiple times
#ifndef Tutorial1_HEADER
#define Tutorial1_HEADER
// We need the Plasma Applet headers
#include <KIcon>

#include <Plasma/Applet>
#include <Plasma/Svg>
#include <Plasma/PopupApplet>
#include <QDBusInterface>
#include <QString>

#include "ui_eyerest-config.h"

#include "eyerest_dbus.h"

class QSizeF;
class QAction;

namespace Plasma
{
    class Label;
}

// Define our plasma Applet
class PlasmaEyerest: public Plasma::Applet
{
    Q_OBJECT
public:
        // Basic Create/Destroy
        PlasmaEyerest(QObject *parent, const QVariantList &args);
        ~PlasmaEyerest();

        // The paintInterface procedure paints the applet to screen
        void paintInterface(QPainter *p,
                const QStyleOptionGraphicsItem *option,
                const QRect& contentsRect);
        virtual void init();

        virtual void createConfigurationInterface(KConfigDialog* parent);

        QList<QAction*>  contextualActions ();

private:
        //Plasma::Label *m_label;
        QString m_time_text;
        QAction *m_menu_state;

        org::zlbruce::eyerest::basic* m_eye_proxy;
        QDBusInterface* m_notify_proxy;

        uint m_notify_id;
        bool m_notified;            // 是否通知过了

        void send_notification();
        void prepare_font(QFont &font, QRect &rect, const QString &text);

        // config
        Ui::Config m_config;
        QString m_format;
        uint m_notify_time;
        QFont m_font;
        QColor m_color;

private Q_SLOTS: 
        void on_status_change(uint time_remain, const QString state);
        void on_delay(int time);
        void on_pause();
        void on_unpause();
        void on_rest_now();
        void on_notify_close(uint id, uint reason);
        void on_notify_action_invoked(uint id, QString action_key);

        void on_config_accepted();
};

#endif
