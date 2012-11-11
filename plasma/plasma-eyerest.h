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

#include "eyerest_dbus.h"

class QSizeF;
class QAction;

namespace Plasma
{
    class Label;
}

// Define our plasma Applet
class PlasmaEyerest: public Plasma::PopupApplet
{
    Q_OBJECT
public:
        // Basic Create/Destroy
        PlasmaEyerest(QObject *parent, const QVariantList &args);
        ~PlasmaEyerest();

        // The paintInterface procedure paints the applet to screen
        //void paintInterface(QPainter *p,
        //        const QStyleOptionGraphicsItem *option,
        //        const QRect& contentsRect);
        void init();

        QList<QAction*>  contextualActions ();

private:
        Plasma::Label *m_label;
        QAction *m_menu_state;

        org::zlbruce::eyerest::basic* m_eye_proxy;
        QDBusInterface* m_notify_proxy;

        uint m_notify_id;
        bool m_notified;            // 是否通知过了

        void send_notification();

private Q_SLOTS: 
        void on_status_change(uint time_remain, const QString state);
        void on_delay(int time);
        void on_pause();
        void on_unpause();
        void on_rest_now();
        void on_notify_close(uint id, uint reason);
        void on_notify_action_invoked(uint id, QString action_key);
};

#endif
