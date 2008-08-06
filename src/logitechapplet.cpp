/***************************************************************************
 *   Copyright (C) 2008 by Lawrence Lee                                    *
 *   valheru.ashen.shugar@gmail.com                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <KDE/KActionCollection>
#include <KDE/KApplication>
#include <KDE/KStandardAction>
#include <KDE/KSystemTrayIcon>
#include <QDBusConnection>
#include <QTimerEvent>
#include "logitechappletinterface.h"
#include "logitechapplet.h"
#include "logitechwidget.h"

LogitechApplet::LogitechApplet ( QWidget *parent )
    : KXmlGuiWindow ( parent ), ok_to_close ( false ), connected_to_daemon ( false )
{
    interface = new ComGooglecodeLogitechg15Interface ( "com.googlecode.logitechg15", "/com/googlecode/logitechg15", QDBusConnection::systemBus(), this );
    m_widget = new QWidget( this );
    QHBoxLayout *layout = new QHBoxLayout( m_widget );
    logitechWidget = new LogitechWidget( interface, m_widget );
    layout->addWidget( logitechWidget );
    setCentralWidget( m_widget );
    setupActions();
    setupGUI();
    setAutoSaveSettings();
    trayIcon = new KSystemTrayIcon( QIcon( ":/pics/logitech.png" ), this );
    connect( trayIcon, SIGNAL( quitSelected() ), SLOT( exit() ) );
    trayIcon->show();
    startTimer ( 1000 );
}

LogitechApplet::~LogitechApplet()
{
    delete logitechWidget;
    delete m_widget;
    delete interface;
    delete trayIcon;
}

void LogitechApplet::timerEvent( QTimerEvent *event )
{
    Q_UNUSED ( event );

    if ( interface->isValid() ) {
        connected_to_daemon = true;
        m_widget->setEnabled ( true );

    } else {
        connected_to_daemon = false;
        m_widget->setEnabled( false );
    }
}

void LogitechApplet::setEnabled ( bool enabled )
{
    m_widget->setEnabled ( enabled );
//  LCDBrightnessDark->setEnabled( enabled );
//  LCDBrightnessMedium->setEnabled( enabled );
//  LCDBrightnessBright->setEnabled( enabled );
//  LCDContrastLow->setEnabled( enabled );
//  LCDContrastMedium->setEnabled( enabled );
//  LCDContrastHigh->setEnabled( enabled );
//  KeyboardBrightnessDark->setEnabled( enabled );
//  KeyboardBrightnessMedium->setEnabled( enabled );
//  KeyboardBrightnessBright->setEnabled( enabled );
}

void LogitechApplet::setupActions()
{
    setStandardToolBarMenuEnabled( false );
    createStandardStatusBarAction();
    KStandardAction::quit( this, SLOT( exit() ), actionCollection() );
}

bool LogitechApplet::queryClose()
{
    if ( !ok_to_close ) {
        hide();
    }

    return ok_to_close;
}

bool LogitechApplet::queryExit()
{
    return true;
}

void LogitechApplet::exit()
{
    ok_to_close = true;
    kapp->setQuitOnLastWindowClosed ( true );
    close();
}

#include "logitechapplet.moc"
