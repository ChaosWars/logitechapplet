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
#ifndef LOGITECHG15PLUGIN_H
#define LOGITECHG15PLUGIN_H

#include <QObject>

class QWidget;

/**
 * @author Lawrence Lee <valheru.ashen.shugar@gmail.com>
 */
class LogitechG15Plugin : public QObject
{
    Q_OBJECT

    public:
        LogitechG15Plugin( QWidget *widget, QObject *parent = 0 );
        virtual ~LogitechG15Plugin();
        QWidget* widget(){ return m_widget; }

    private:
        QWidget *m_widget;
};

#endif
