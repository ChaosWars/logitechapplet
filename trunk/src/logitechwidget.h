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

/**
 * @class LogitechWidget logitechwidget.h
 */
#ifndef LOGITECHWIDGET_H
#define LOGITECHWIDGET_H

#include <KDE/KConfigGroup>
#include "ui_logitechwidget.h"

class ComGooglecodeLogitechg15Interface;

/**
 * @brief The central widget for Logitech Applet
 *
 * This widget provides all widget interfaces to the logitechg15 daemon
 *
 * @author Lawrence Lee <valheru.ashen.shugar@gmail.com>
 */
class LogitechWidget : public QWidget, public Ui::LogitechWidget
{
    Q_OBJECT

    public:
        LogitechWidget( ComGooglecodeLogitechg15Interface *interface, QWidget *parent = 0 );
        ~LogitechWidget();
        void readProperties( const KConfigGroup &group );
        void saveProperties( KConfigGroup &group );
        void sendSettingsToDaemon();

    public Q_SLOTS:
        void KeyboardBrightnessSet();
        void LCDBrightnessSet();
        void LCDContrastSet();
        void DaemonSetKeyboardBrightness ( int brightness );
        void DaemonSetLCDBrightness ( int brightness );
        void DaemonSetLCDContrast ( int contrast );
        void blank_screen();
        void show_logo();

    private:
        ComGooglecodeLogitechg15Interface *m_interface;
};

#endif
