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

#include "logitechappletinterface.h"
#include "logitechwidget.h"

LogitechWidget::LogitechWidget( ComGooglecodeLogitechg15Interface *interface, QWidget *parent )
 : QWidget(parent), m_interface( interface )
{
    setupUi( this );
    connect ( kcfg_LCDContrastLow, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( kcfg_LCDContrastMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( kcfg_LCDContrastHigh, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDContrastSet() ) );
    connect ( kcfg_LCDBrightnessDark, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( kcfg_LCDBrightnessMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( kcfg_LCDBrightnessBright, SIGNAL ( toggled ( bool ) ), this, SLOT ( LCDBrightnessSet() ) );
    connect ( kcfg_KeyboardBrightnessDark, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( kcfg_KeyboardBrightnessMedium, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( kcfg_KeyboardBrightnessBright, SIGNAL ( toggled ( bool ) ), this, SLOT ( KeyboardBrightnessSet() ) );
    connect ( kcfg_BlankScreen, SIGNAL ( toggled ( bool ) ), this, SLOT ( blank_screen() ) );
    connect ( kcfg_ShowLogo, SIGNAL ( toggled ( bool ) ), this, SLOT ( show_logo() ) );
}

LogitechWidget::~LogitechWidget()
{
}

void LogitechWidget::KeyboardBrightnessSet()
{
    if ( kcfg_KeyboardBrightnessDark->isChecked() )

        m_interface->set_kb_brightness ( 0 );
    else if ( kcfg_KeyboardBrightnessMedium->isChecked() )

        m_interface->set_kb_brightness ( 1 );
    else if ( kcfg_KeyboardBrightnessBright->isChecked() )

        m_interface->set_kb_brightness ( 2 );
}

void LogitechWidget::LCDBrightnessSet()
{
    if ( kcfg_LCDBrightnessDark->isChecked() )

        m_interface->set_lcd_brightness ( 0 );
    else if ( kcfg_LCDBrightnessMedium->isChecked() )

        m_interface->set_lcd_brightness ( 1 );
    else if ( kcfg_LCDBrightnessBright->isChecked() )

        m_interface->set_lcd_brightness ( 2 );
}

void LogitechWidget::LCDContrastSet()
{
    if ( kcfg_LCDContrastLow->isChecked() )

        m_interface->set_lcd_contrast ( 0 );
    else if ( kcfg_LCDContrastMedium->isChecked() )

        m_interface->set_lcd_contrast ( 1 );
    else if ( kcfg_LCDContrastHigh->isChecked() )

        m_interface->set_lcd_contrast ( 2 );
}

void LogitechWidget::DaemonSetKeyboardBrightness ( int brightness )
{
    switch ( brightness ) {
        case 0:
            kcfg_KeyboardBrightnessDark->setChecked ( true );
            break;
        case 1:
            kcfg_KeyboardBrightnessMedium->setChecked ( true );
            break;
        case 2:
            kcfg_KeyboardBrightnessBright->setChecked ( true );
            break;
        default:
            kcfg_KeyboardBrightnessDark->setChecked ( true );
            break;
    }
}

void LogitechWidget::DaemonSetLCDBrightness ( int brightness )
{
    switch ( brightness ) {
        case 0:
            kcfg_LCDBrightnessDark->setChecked ( true );
            break;
        case 1:
            kcfg_LCDBrightnessMedium->setChecked ( true );
            break;
        case 2:
            kcfg_LCDBrightnessBright->setChecked ( true );
            break;
        default:
            kcfg_LCDBrightnessDark->setChecked ( true );
            break;
    }
}

void LogitechWidget::DaemonSetLCDContrast ( int contrast )
{
    switch ( contrast ) {
        case 0:
            kcfg_LCDContrastLow->setChecked ( true );
            break;
        case 1:
            kcfg_LCDContrastMedium->setChecked ( true );
            break;
        case 2:
            kcfg_LCDContrastHigh->setChecked ( true );
            break;
        default:
            kcfg_LCDContrastLow->setChecked ( true );
            break;
    }
}

void LogitechWidget::blank_screen()
{
    if ( kcfg_BlankScreen->isChecked() )
        m_interface->blank_screen();
}

void LogitechWidget::show_logo()
{
    if ( kcfg_ShowLogo->isChecked() )
        m_interface->show_logo();
}

#include "logitechwidget.moc"
