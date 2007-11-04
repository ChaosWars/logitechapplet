/***************************************************************************
 *   Copyright (C) 2007 by Lawrence Lee   *
 *   valheru@facticius.net   *
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
#include <QCloseEvent>
#include "applet_interface.h"
#include "logitechapplet.h"

bool ok_to_close;

LogitechApplet::LogitechApplet()
{
	ok_to_close = false;
	setupUi( this );
	systrayicon = new QSystemTrayIcon( QIcon( ":/pics/logitech_logo.png" ), this );
	systrayicon->setContextMenu( menu_Action );
	systrayicon->show();
	connect( systrayicon, SIGNAL( activated ( QSystemTrayIcon::ActivationReason ) ), this, SLOT( systemTrayClicked( QSystemTrayIcon::ActivationReason ) ) );
	connect( action_Exit, SIGNAL( triggered() ), this, SLOT( shutdown() ) );
	connect( LCDContrastLow, SIGNAL( toggled( bool ) ), this, SLOT( LCDContrastSet() ) );
	connect( LCDContrastMedium, SIGNAL( toggled( bool ) ), this, SLOT( LCDContrastSet() ) );
	connect( LCDContrastHigh, SIGNAL( toggled( bool ) ), this, SLOT( LCDContrastSet() ) );
	connect( LCDBrightnessDark, SIGNAL( toggled( bool ) ), this, SLOT( LCDBrightnessSet() ) );
	connect( LCDBrightnessMedium, SIGNAL( toggled( bool ) ), this, SLOT( LCDBrightnessSet() ) );
	connect( LCDBrightnessBright, SIGNAL( toggled( bool ) ), this, SLOT( LCDBrightnessSet() ) );
	connect( KeyboardBrightnessDark, SIGNAL( toggled( bool ) ), this, SLOT( KBBrightnessSet() ) );
	connect( KeyboardBrightnessMedium, SIGNAL( toggled( bool ) ), this, SLOT( KBBrightnessSet() ) );
	connect( KeyboardBrightnessBright, SIGNAL( toggled( bool ) ), this, SLOT( KBBrightnessSet() ) );
	interface = new LogitechDaemonInterface( "org.freedesktop.LogitechDaemon", "/Main", QDBusConnection::systemBus(), this );
	startTimer( 1000 );
	
}

LogitechApplet::~LogitechApplet()
{
	delete systrayicon;
	delete interface;
}

void LogitechApplet::timerEvent( QTimerEvent *event )
{
	Q_UNUSED(event);
	if ( interface->isValid() )
		setEnabled( true );
	else
		setEnabled( false );
}

void LogitechApplet::closeEvent( QCloseEvent *event )
{
	if( ok_to_close ){
		event->accept();
	}else{
		event->ignore();
		hide();
	}
}

void LogitechApplet::systemTrayClicked( QSystemTrayIcon::ActivationReason reason )
{
	if( reason != QSystemTrayIcon::Trigger )
		return;
	
	if( isVisible() )
		hide();
	else
		show();
}

void LogitechApplet::shutdown()
{
	ok_to_close = true;
	close();
}

void LogitechApplet::setEnabled( bool enabled )
{
	LCDBrightnessDark->setEnabled( enabled );
	LCDBrightnessMedium->setEnabled( enabled );
	LCDBrightnessBright-> setEnabled( enabled );
	LCDContrastLow->setEnabled( enabled );
	LCDContrastMedium->setEnabled( enabled );
	LCDContrastHigh->setEnabled( enabled );
	KeyboardBrightnessDark->setEnabled( enabled );
	KeyboardBrightnessMedium->setEnabled( enabled );
	KeyboardBrightnessBright->setEnabled( enabled );
}

void LogitechApplet::KBBrightnessSet()
{
}

void LogitechApplet::LCDBrightnessSet()
{
}

void LogitechApplet::LCDContrastSet()
{
}

#include "logitechapplet.moc"
