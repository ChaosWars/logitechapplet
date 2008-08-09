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
#include <KDE/KCmdLineArgs>
#include <KDE/KConfigDialog>
#include <KDE/KDebug>
#include <KDE/KGlobal>
#include <KDE/KIconLoader>
#include <KDE/KLocale>
#include <KDE/KPageWidget>
#include <KDE/KPageWidgetItem>
#include <KDE/KStandardAction>
#include <KDE/KSystemTrayIcon>
#include <QTimerEvent>
#include "appletsettings.h"
#include "generalsettingswidget.h"
#include "logitechappletinterface.h"
#include "logitechapplet.h"
#include "logitechwidget.h"

LogitechApplet::LogitechApplet ( QWidget *parent )
    : KXmlGuiWindow ( parent ), ok_to_close ( false ), connected_to_daemon ( false )
{
    KIconLoader *iconLoader = KIconLoader::global();
    interface = new ComGooglecodeLogitechg15Interface ( "com.googlecode.logitechg15", "/com/googlecode/logitechg15", QDBusConnection::systemBus(), this );
    interface->blank_screen();
    m_widget = new KPageWidget( this );
    logitechWidget = new LogitechWidget( interface, m_widget );
    logitechWidgetItem = new KPageWidgetItem( logitechWidget, i18n( "Keyboard Settings" ) );
    logitechWidgetItem->setHeader( i18n( "Keyboard Settings for Logitech G15" ) );
    logitechWidgetItem->setIcon( KIcon( iconLoader->loadIcon( "logitech", KIconLoader::User ) ) );
    m_widget->addPage( logitechWidgetItem );
    QWidget *widget = new QWidget();
    m_widget->addPage( widget, "Placeholder");
    setCentralWidget( m_widget );
    setupActions();
    setupGUI();
    setAutoSaveSettings();
    config = KGlobal::config();
    trayIcon = new KSystemTrayIcon( KIcon( iconLoader->loadIcon( "logitech", KIconLoader::User ) ), this );
    connect( trayIcon, SIGNAL( quitSelected() ), SLOT( exit() ) );
    trayIcon->show();
    readProperties( KConfigGroup( config, "WidgetSettings") );
    startTimer ( 1000 );
}

LogitechApplet::~LogitechApplet()
{
    KConfigGroup configGroup( config, "WidgetSettings" );
    logitechWidget->saveProperties( configGroup );
    delete m_widget;
    delete interface;
    delete trayIcon;
}

void LogitechApplet::loadSettings( QString /*settings*/ )
{
}

void LogitechApplet::optionsConfigure()
{
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }

    KConfigDialog *dialog = new KConfigDialog( this, "settings", AppletSettings::self() );
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    QWidget *generalSettingsPage = new QWidget();
    dialog->addPage( new GeneralSettingsWidget( generalSettingsPage ), i18n( "General" ), "preferences-system-general" );
    connect( dialog, SIGNAL( settingsChanged( QString ) ), this, SLOT( loadSettings( QString ) ) );
    dialog->show();
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

void LogitechApplet::readProperties( const KConfigGroup &configGroup )
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
    if( configGroup.name() == "WidgetSettings" )
        logitechWidget->readProperties( configGroup );
}

void LogitechApplet::saveProperties( KConfigGroup& /*configGroup*/ )
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void LogitechApplet::setEnabled ( bool enabled )
{
    m_widget->setEnabled ( enabled );
}

void LogitechApplet::setupActions()
{
    setStandardToolBarMenuEnabled( false );
    createStandardStatusBarAction();
    KStandardAction::quit( this, SLOT( exit() ), actionCollection() );
    preferences = KStandardAction::preferences( this, SLOT( optionsConfigure() ), actionCollection() );
}

void LogitechApplet::timerEvent( QTimerEvent *event )
{
    Q_UNUSED ( event );

    if ( interface->isValid() && !connected_to_daemon ) {
        connected_to_daemon = true;
        m_widget->setEnabled ( true );
        logitechWidget->sendSettingsToDaemon();
    } else if( !interface->isValid() && connected_to_daemon ){
        connected_to_daemon = false;
        m_widget->setEnabled( false );
    }
}

void LogitechApplet::exit()
{
    ok_to_close = true;
    kapp->setQuitOnLastWindowClosed ( true );
    close();
}

#include "logitechapplet.moc"
