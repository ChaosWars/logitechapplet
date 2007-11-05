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
#ifndef _LOGITECHAPPLET_H_
#define _LOGITECHAPPLET_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "ui_logitechapplet.h"

class OrgFreedesktopLogitechDaemonInterface;

class LogitechApplet : public QMainWindow, Ui::LogitechApplet
{
	Q_OBJECT

	public:
		LogitechApplet();
		~LogitechApplet();

	protected:
		void timerEvent( QTimerEvent *event );
		void closeEvent( QCloseEvent *event );

	private:
		OrgFreedesktopLogitechDaemonInterface *interface;
		QSystemTrayIcon *systrayicon;
		void setEnabled( bool enabled );

	private Q_SLOTS:
		
		void KBBrightnessSet();
		void LCDBrightnessSet();
		void LCDContrastSet();
		void kb_brightness_set( int brightness );
		void lcd_brightness_set( int brightness );
		void lcd_contrast_set( int contrast );
		void shutdown();
		void systemTrayClicked( QSystemTrayIcon::ActivationReason );
};

#endif //	_LOGITECHAPPLET_H_
