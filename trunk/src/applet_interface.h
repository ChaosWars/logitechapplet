/*
 * This file was generated by dbusxml2cpp version 0.6
 * Command line was: dbusxml2cpp -c LogitechDaemonInterface -p applet_interface.h:applet_interface.cpp applet.xml
 *
 * dbusxml2cpp is Copyright (C) 2006 Trolltech ASA. All rights reserved.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef APPLET_INTERFACE_H_1194173830
#define APPLET_INTERFACE_H_1194173830

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.freedesktop.LogitechDaemon.Interface
 */
class LogitechDaemonInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.freedesktop.LogitechDaemon.Interface"; }

public:
    LogitechDaemonInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LogitechDaemonInterface();

public Q_SLOTS: // METHODS
    inline QDBusReply<void> setKBBrightness()
    {
        QList<QVariant> argumentList;
        return callWithArgumentList(QDBus::Block, QLatin1String("setKBBrightness"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace freedesktop {
    namespace LogitechDaemon {
      typedef ::LogitechDaemonInterface Interface;
    }
  }
}
#endif
