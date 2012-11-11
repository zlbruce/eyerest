#include "plasma-eyerest.h"
 
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QAction>
#include <QTime>
#include <QGraphicsLinearLayout>
 
#include <plasma/theme.h>
#include <plasma/widgets/lineedit.h>
#include <plasma/widgets/label.h>
#include <plasma/widgets/pushbutton.h>

namespace 
{
    const uint NOTIFY_TIME = 60;
}

PlasmaEyerest::PlasmaEyerest(QObject *parent, const QVariantList &args)
    : Plasma::PopupApplet(parent, args),
    m_label(NULL),
    m_menu_state(NULL),
    m_eye_proxy(NULL),
    m_notify_proxy(NULL),
    m_notify_id(0),
    m_notified(true)
{
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    resize(200, 100);
}


PlasmaEyerest::~PlasmaEyerest()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

QList<QAction*> PlasmaEyerest::contextualActions()
{
    m_menu_state = new QAction(this);
    m_menu_state->setText("State:");

    QAction* sep0 = new QAction(this);
    sep0->setSeparator(true);

    QAction* delay3min = new QAction(this);
    delay3min->setText("Delay 3 min");

    QAction* delay5min = new QAction(this);
    delay5min->setText("Delay 5 min");

    QSignalMapper* signalMapper = new QSignalMapper (this);
    connect (delay3min, SIGNAL(triggered()), signalMapper, SLOT(map())) ;
    connect (delay5min, SIGNAL(triggered()), signalMapper, SLOT(map())) ;

    signalMapper->setMapping (delay3min, 180) ;
    signalMapper->setMapping (delay5min, 300) ;

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(on_delay(int))) ;


    QAction* sep1 = new QAction(this);
    sep1->setSeparator(true);

    QAction* pause = new QAction(this);
    pause->setText("Pause");
    connect(pause, SIGNAL(triggered()), this, SLOT(on_pause()));

    QAction* unpause = new QAction(this);
    unpause->setText("Continue");
    connect(unpause, SIGNAL(triggered()), this, SLOT(on_unpause()));

    QAction* rest_now = new QAction(this);
    rest_now->setText("Rest now");
    connect(rest_now, SIGNAL(triggered()), this, SLOT(on_rest_now()));

    /*
    QAction* test_notify = new QAction(this);
    test_notify->setText("Notify");

    connect(test_notify, SIGNAL(triggered()), this, SLOT(on_notify()));
    */

    QList<QAction*> contextualActions;
    contextualActions << m_menu_state
                      << sep0
                      << delay3min
                      << delay5min
                      << sep1
                      << pause
                      << unpause
                      << rest_now;

    return contextualActions;
}


void PlasmaEyerest::init()
{

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    layout->setOrientation(Qt::Vertical); //so widgets will be stacked up/down

    m_label = new Plasma::Label(this);
    m_label->setText("eyerest");


    layout->addItem(m_label);

    m_eye_proxy = new org::zlbruce::eyerest::basic("org.zlbruce.eyerest",
            "/",
            QDBusConnection::sessionBus(),
            this);

    connect(m_eye_proxy, SIGNAL(status(uint, const QString)), this, SLOT(on_status_change(uint, const QString)));

    const QString dbusNotifyServiceName = "org.freedesktop.Notifications";
    const QString dbusNotifyInterfaceName = "org.freedesktop.Notifications";
    const QString dbusNotifyPath = "/org/freedesktop/Notifications";
    m_notify_proxy = new QDBusInterface(dbusNotifyServiceName,
            dbusNotifyPath,
            dbusNotifyInterfaceName,
            QDBusConnection::sessionBus(),
            this);
    m_notify_proxy->connection().connect(dbusNotifyServiceName,
            dbusNotifyPath,
            dbusNotifyInterfaceName,
            "NotificationClosed",
            this,
            SLOT(on_notify_close(uint, uint)));
    m_notify_proxy->connection().connect(dbusNotifyServiceName,
            dbusNotifyPath,
            dbusNotifyInterfaceName,
            "ActionInvoked",
            this,
            SLOT(on_notify_action_invoked(uint, QString)));
} 


//void PlasmaEyerest::paintInterface(QPainter *p,
//        const QStyleOptionGraphicsItem *option, const QRect &contentsRect)
//{
//    p->setRenderHint(QPainter::SmoothPixmapTransform);
//    p->setRenderHint(QPainter::Antialiasing);
//
//    // Now we draw the applet, starting with our svg
//    m_svg.resize((int)contentsRect.width(), (int)contentsRect.height());
//    m_svg.paint(p, (int)contentsRect.left(), (int)contentsRect.top());
//
//    // We place the icon and text
//    p->drawPixmap(7, 0, m_icon.pixmap((int)contentsRect.width(),(int)contentsRect.width()-14));
//    p->save();
//    p->setPen(Qt::white);
//    p->drawText(contentsRect,
//            Qt::AlignBottom | Qt::AlignHCenter,
//            "Hello Plasmoid!");
//    p->restore();
//}
void PlasmaEyerest::on_status_change(uint time_remain, const QString state)
{
    QTime tm = QTime().addSecs(time_remain);
    m_label->setText(tm.toString("mm:ss"));
    if(m_menu_state)
    {
        m_menu_state->setText("State: " + state);
    }

    if(state != "ACTIVE")
    {
        return;
    }

    if(time_remain < NOTIFY_TIME)
    {
        if(!m_notified)
            send_notification();
    }
    else
    {
        m_notified = false;
        if(m_notify_id != 0)
        {
            m_notify_proxy->call("CloseNotification", m_notify_id);
        }
    }
}

void PlasmaEyerest::on_delay(int time)
{
    m_eye_proxy->delay(time);
}
void PlasmaEyerest::on_pause()
{
    m_eye_proxy->pause();
}
void PlasmaEyerest::on_unpause()
{
    m_eye_proxy->unpause();
}
void PlasmaEyerest::on_rest_now()
{
    m_eye_proxy->rest_now();
}
/**
 * Display a passive notification popup using the D-Bus interface, if possible.
 */
void PlasmaEyerest::send_notification()
{
  QList<QVariant> args;

  args.append("Eyerest"); // app_name
  args.append(m_notify_id); // replaces_id
  args.append("dialog-information"); // app_icon
  args.append("It's time for a break"); // summary
  args.append(m_label->text()); // body
  args.append(QStringList() << "1" << "I Know" << "2" << "Delay 3 min"); // actions - (key,action)
  args.append(QVariantMap()); // hints - unused atm
  args.append(NOTIFY_TIME * 1000); // expire timout

  QDBusReply<uint> reply = m_notify_proxy->callWithArgumentList(QDBus::AutoDetect, "Notify", args);

  if(reply.isValid())
  {
      m_notify_id = reply.value();
  }

}

void PlasmaEyerest::on_notify_close(uint id, uint reason)
{
    //Q_UNUSED(reason);
    printf("id = %u, reason = %u\n", id, reason);
    // 只处理我们发出去的消息通知
    if(id == m_notify_id)
    {
        m_notify_id = 0;
        m_notified = true;
    }
}

void PlasmaEyerest::on_notify_action_invoked(uint id, QString action_key)
{
    if(id == m_notify_id && action_key == "2")
    {
        m_eye_proxy->delay(180);
    }
}
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(eyerest, PlasmaEyerest)

#include "plasma-eyerest.moc"


