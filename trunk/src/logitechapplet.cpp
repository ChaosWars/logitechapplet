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
#include <QApplication>
#include <QCloseEvent>
#include "appletinterface.h"
#include "logitechapplet.h"

static int MouseButtons[] = { 3, 4, 5, 6, 7, 8, 9, 11, 13 };

LogitechApplet::LogitechApplet()
{
	ok_to_close = false;
	connected_to_daemon = false;
	setupUi( this );
	systrayicon = new QSystemTrayIcon( QIcon( ":/pics/logitech-logo.png" ), this );
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
	connect( BlankScreen, SIGNAL( toggled( bool ) ), this, SLOT( blank_screen() ) );
	connect( ShowLogo, SIGNAL( toggled( bool ) ), this, SLOT( show_logo() ) );
	interface = new OrgFreedesktopLogitechDaemonInterface( "org.freedesktop.LogitechDaemon", "/org/freedesktop/LogitechDaemon", QDBusConnection::systemBus(), this );
	startTimer( 1000 );
	connect( interface, SIGNAL( lcd_brightness_set( int ) ), this, SLOT( DaemonSetLCDBrightness( int ) ) );
	connect( interface, SIGNAL( lcd_contrast_set( int ) ), this, SLOT( DaemonSetLCDContrast( int ) ) );
	connect( interface, SIGNAL( kb_brightness_set( int ) ), this, SLOT( DaemonSetKbBrightness( int ) ) );

    //Setup mouse widget
    connect( freeSpinRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( freeSpinToggled( bool ) ) );
    connect( clickToClickRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( clickToClickToggled( bool ) ) );
    connect( buttonComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( clickToClickButtonChanged( int ) ) );
    connect( speedSpinBox, SIGNAL( valueChanged( int ) ), this, SLOT( speedChanged( int ) ) );
    connect( speedRadioButton, SIGNAL( toggled( bool ) ), speedSpinBox, SLOT( setEnabled( bool ) ) );
    connect( speedRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( speedRadioButtonToggled( bool ) ) );
    connect( modeChangeRadioButton, SIGNAL( toggled( bool ) ), buttonComboBox, SLOT( setEnabled( bool ) ) );
    connect( modeChangeRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( modeChangedRadioButtonToggled( bool ) ) );
    connect( freeSpinOnWheelMoveRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( freeSpinOnWheelMoveChanged( bool ) ) );
    connect( clickToClickOnWheelMoveRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( clickToClickOnWheelMoveChanged( bool ) ) );
    connect( unknownRadioButton, SIGNAL( toggled( bool ) ), this, SLOT( unknownChanged( bool ) ) );
}

LogitechApplet::~LogitechApplet()
{
    delete interface;
	delete systrayicon;
}

void LogitechApplet::timerEvent( QTimerEvent *event )
{
	Q_UNUSED(event);
	if ( interface->isValid() ){
		connected_to_daemon = true;
		setEnabled( true );
	}else{
		connected_to_daemon = false;
		setEnabled( false );
	}
}

void LogitechApplet::closeEvent( QCloseEvent *event )
{
	if( ok_to_close ){
		event->accept();
        QApplication::quit();
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
	LCDBrightnessBright->setEnabled( enabled );
	LCDContrastLow->setEnabled( enabled );
	LCDContrastMedium->setEnabled( enabled );
	LCDContrastHigh->setEnabled( enabled );
	KeyboardBrightnessDark->setEnabled( enabled );
	KeyboardBrightnessMedium->setEnabled( enabled );
	KeyboardBrightnessBright->setEnabled( enabled );
}

void LogitechApplet::KBBrightnessSet()
{
	if( KeyboardBrightnessDark->isChecked() )
		interface->set_kb_brightness( 0 );
	else if( KeyboardBrightnessMedium->isChecked() )
		interface->set_kb_brightness( 1 );
	else if( KeyboardBrightnessBright->isChecked() )
		interface->set_kb_brightness( 2 );
}

void LogitechApplet::LCDBrightnessSet()
{
	if( LCDBrightnessDark->isChecked() )
		interface->set_lcd_brightness( 0 );
	else if( LCDBrightnessMedium->isChecked() )
		interface->set_lcd_brightness( 1 );
	else if( LCDBrightnessBright->isChecked() )
		interface->set_lcd_brightness( 2 );
}

void LogitechApplet::LCDContrastSet()
{
	if( LCDContrastLow->isChecked() )
		interface->set_lcd_contrast( 0 );
	else if( LCDContrastMedium->isChecked() )
		interface->set_lcd_contrast( 1 );
	else if( LCDContrastHigh->isChecked() )
		interface->set_lcd_contrast( 2 );
}

void LogitechApplet::DaemonSetKbBrightness( int brightness )
{
	switch( brightness ){
		case 0:
			KeyboardBrightnessDark->setChecked( true );
			break;
		case 1:
			KeyboardBrightnessMedium->setChecked( true );
			break;
		case 2:
			KeyboardBrightnessBright->setChecked( true );
			break;
		default:
			KeyboardBrightnessDark->setChecked( true );
			break;
	}
}

void LogitechApplet::DaemonSetLCDBrightness( int brightness )
{
	switch( brightness ){
		case 0:
			LCDBrightnessDark->setChecked( true );
			break;
		case 1:
			LCDBrightnessMedium->setChecked( true );
			break;
		case 2:
			LCDBrightnessBright->setChecked( true );
			break;
		default:
			LCDBrightnessDark->setChecked( true );
			break;
	}
}

void LogitechApplet::DaemonSetLCDContrast( int contrast )
{
	switch( contrast ){
		case 0:
			LCDContrastLow->setChecked( true );
			break;
		case 1:
			LCDContrastMedium->setChecked( true );
			break;
		case 2:
			LCDContrastHigh->setChecked( true );
			break;
		default:
			LCDContrastLow->setChecked( true );
			break;
	}
}

void LogitechApplet::blank_screen()
{
	if( BlankScreen->isChecked() )
		interface->blank_screen();
}

void LogitechApplet::show_logo()
{
	if( ShowLogo->isChecked() )
		interface->show_logo();
}

void LogitechApplet::freeSpinToggled( bool on )
{
    if( on ){
        interface->set_mouse_free_spin();
    }
}

void LogitechApplet::clickToClickToggled( bool on )
{
    clickToClickGroupBox->setEnabled( on );

    if( on ){
        if( modeChangeRadioButton->isChecked() ){
            interface->set_mouse_manual_mode( MouseButtons[buttonComboBox->currentIndex()] );
        }else{
            if( speedRadioButton->isChecked() ){
                interface->set_mouse_auto_mode( speedSpinBox->value() );
            }
        }
    }
}

void LogitechApplet::clickToClickButtonChanged( int button )
{
    interface->set_mouse_manual_mode( MouseButtons[button] );
}

void LogitechApplet::speedChanged( int speed )
{
    if( speed >= 0 && speed <= 50 )
        interface->set_mouse_auto_mode( speed );
}

void LogitechApplet::freeSpinOnWheelMoveChanged( bool on )
{
    if( on ){
        interface->set_mouse_fs_on_wheel_move();
    }
}

void LogitechApplet::clickToClickOnWheelMoveChanged( bool on )
{
    if( on ){
        interface->set_mouse_cc_on_wheel_move();
    }
}

void LogitechApplet::unknownChanged( bool on )
{
    if( on ){
        interface->set_mouse_unknown();
    }
}

void LogitechApplet::speedRadioButtonToggled( bool on )
{
    if( on ){
        speedChanged( speedSpinBox->value() );
    }
}

void LogitechApplet::modeChangedRadioButtonToggled( bool on )
{
    if( on ){
        clickToClickButtonChanged( buttonComboBox->currentIndex() );
    }
}

#include "logitechapplet.moc"
