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

#include <KDE/KDebug>
#include <KDE/KGlobal>
#include "logitechappletinterface.h"
#include "logitechwidget.h"

LogitechWidget::LogitechWidget( ComGooglecodeLogitechg15Interface *interface, QWidget *parent )
 : QWidget(parent)
{
    m_interface = interface;
    setupUi( this );
    connect ( LCDBrightnessDark, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( LCDBrightnessMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( LCDBrightnessBright, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( LCDContrastLow, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( LCDContrastMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( LCDContrastHigh, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( KeyboardBrightnessDark, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( KeyboardBrightnessMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( KeyboardBrightnessBright, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( BlankScreen, SIGNAL ( toggled ( bool ) ), this, SLOT ( blank_screen() ) );
    connect ( ShowLogo, SIGNAL ( toggled ( bool ) ), this, SLOT ( show_logo() ) );
    connect( interface, SIGNAL( kb_brightness_set( int ) ), this, SLOT( DaemonSetKeyboardBrightness( int ) ) );
    connect( interface, SIGNAL( lcd_brightness_set( int ) ), this, SLOT( DaemonSetLCDBrightness( int ) ) );
    connect( interface, SIGNAL( lcd_contrast_set( int ) ), this, SLOT( DaemonSetLCDContrast( int ) ) );
}

LogitechWidget::~LogitechWidget()
{
}

void LogitechWidget::readProperties( const KConfigGroup &group )
{
    LCDBrightnessDark->setChecked( group.readEntry( "LCDBrightnessDark", false ) );
    LCDBrightnessMedium->setChecked( group.readEntry( "LCDBrightnessMedium", true ) );
    LCDBrightnessBright->setChecked( group.readEntry( "LCDBrightnessBright", false ) );
    LCDContrastLow->setChecked( group.readEntry( "LCDContrastLow", false ) );
    LCDContrastMedium->setChecked( group.readEntry( "LCDContrastMeduim", true ) );
    LCDContrastHigh->setChecked( group.readEntry( "LCDContrastHigh", false ) );
    KeyboardBrightnessDark->setChecked( group.readEntry( "KeyboardBrightnessDark", false ) );
    KeyboardBrightnessMedium->setChecked( group.readEntry( "KeyboardBrightnessMedium", true ) );
    KeyboardBrightnessBright->setChecked( group.readEntry( "KeyboardBrightnessBright", false ) );
    BlankScreen->setChecked( group.readEntry( "BlankScreen", false ) );
    ShowLogo->setChecked( group.readEntry( "ShowLogo", true ) );
}

void LogitechWidget::saveProperties( KConfigGroup &group )
{
    group.writeEntry( "LCDBrightnessDark", LCDBrightnessDark->isChecked() );
    group.writeEntry( "LCDBrightnessMedium", LCDBrightnessMedium->isChecked() );
    group.writeEntry( "LCDBrightnessBright", LCDBrightnessBright->isChecked() );
    group.writeEntry( "LCDContrastLow", LCDContrastLow->isChecked() );
    group.writeEntry( "LCDContrastMeduim", LCDContrastMedium->isChecked() );
    group.writeEntry( "LCDContrastHigh", LCDContrastHigh->isChecked() );
    group.writeEntry( "KeyboardBrightnessDark", KeyboardBrightnessDark->isChecked() );
    group.writeEntry( "KeyboardBrightnessMedium", KeyboardBrightnessMedium->isChecked() );
    group.writeEntry( "KeyboardBrightnessBright", KeyboardBrightnessBright->isChecked() );
    group.writeEntry( "BlankScreen", BlankScreen->isChecked() );
    group.writeEntry( "ShowLogo", ShowLogo->isChecked() );
}

void LogitechWidget::KeyboardBrightnessSet()
{
    if ( KeyboardBrightnessDark->isChecked() )
        m_interface->set_kb_brightness ( 0 );
    else if ( KeyboardBrightnessMedium->isChecked() )
        m_interface->set_kb_brightness ( 1 );
    else if ( KeyboardBrightnessBright->isChecked() )
        m_interface->set_kb_brightness ( 2 );
}

void LogitechWidget::LCDBrightnessSet()
{
    if ( LCDBrightnessDark->isChecked() )
        m_interface->set_lcd_brightness ( 0 );
    else if ( LCDBrightnessMedium->isChecked() )
        m_interface->set_lcd_brightness ( 1 );
    else if ( LCDBrightnessBright->isChecked() )
        m_interface->set_lcd_brightness ( 2 );
}

void LogitechWidget::LCDContrastSet()
{
    if ( LCDContrastLow->isChecked() )
        m_interface->set_lcd_contrast ( 0 );
    else if ( LCDContrastMedium->isChecked() )
        m_interface->set_lcd_contrast ( 1 );
    else if ( LCDContrastHigh->isChecked() )
        m_interface->set_lcd_contrast ( 2 );
}

void LogitechWidget::DaemonSetKeyboardBrightness ( int brightness )
{
    switch ( brightness ) {
        case 0:
            if( !KeyboardBrightnessDark->isChecked() )
                KeyboardBrightnessDark->setChecked( true );
            break;
        case 1:
            if( !KeyboardBrightnessMedium->isChecked() )
            KeyboardBrightnessMedium->setChecked( true );
            break;
        case 2:
            if( !KeyboardBrightnessBright->isChecked() )
                KeyboardBrightnessBright->setChecked ( true );
            break;
        default:
            break;
    }
}

void LogitechWidget::DaemonSetLCDBrightness ( int brightness )
{
    switch ( brightness ) {
        case 0:
            if( !LCDBrightnessDark->isChecked() )
                LCDBrightnessDark->setChecked ( true );
            break;
        case 1:
            if( !LCDBrightnessMedium->isChecked() )
                LCDBrightnessMedium->setChecked ( true );
            break;
        case 2:
            if( !LCDBrightnessBright->isChecked() )
                LCDBrightnessBright->setChecked ( true );
            break;
        default:
            break;
    }
}

void LogitechWidget::DaemonSetLCDContrast ( int contrast )
{
    switch ( contrast ) {
        case 0:
            if( !LCDContrastLow->isChecked() )
                LCDContrastLow->setChecked ( true );
            break;
        case 1:
            if( !LCDContrastMedium->isChecked() )
                LCDContrastMedium->setChecked ( true );
            break;
        case 2:
            if( !LCDContrastHigh->isChecked() )
                LCDContrastHigh->setChecked ( true );
            break;
        default:
            break;
    }
}

void LogitechWidget::blank_screen()
{
    if ( BlankScreen->isChecked() )
        m_interface->blank_screen();
}

void LogitechWidget::show_logo()
{
    if ( ShowLogo->isChecked() )
        m_interface->show_logo();
}

#include "logitechwidget.moc"
