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

#include <KDE/KAboutData>
#include <KDE/KDebug>
#include <KDE/KLocalizedString>
#include <KDE/KCmdLineArgs>
#include <KDE/KUniqueApplication>
#include "logitechapplet.h"

static const char description[] = I18N_NOOP( "KDE4 applet for interfacing with the logitechg15 daemon" );
static const char version[] = "1.0";

int main( int argc, char **argv )
{
    KCmdLineOptions options;
    options.add( "+someoptions", ki18n( "Some option" ) );
    KAboutData about( "logitechapplet", "logitechapplet", ki18n( "Logitech Applet" ), version, ki18n( description ), KAboutData::License_GPL,
                      ki18n( "Copyright (c) 2008 Lawrence Lee" ), ki18n( "Applet for interfacing with the logitechg15 daemon" ),
                             "http://logitechapplet.googlecode.com", "http://code.google.com/p/logitechapplet/issues/list" );
    about.addAuthor( ki18n( "Lawrence Lee" ), ki18n( "Lead programmer" ), "valheru.ashen.shugar@gmail.com", "http://logitech.googlecode.com" );
    KCmdLineArgs::init( argc, argv, &about );
    KCmdLineArgs::addCmdLineOptions( options );
    KCmdLineArgs::addTempFileOption();
    KUniqueApplication::addCmdLineOptions();

    if( !KUniqueApplication::start() ){
        kDebug() << i18n( "Logitech Applet is already running!" ) << endl;
        exit( EXIT_FAILURE );
    }

    KUniqueApplication app;
    Q_INIT_RESOURCE( logitechapplet );
    app.setQuitOnLastWindowClosed( false );
    LogitechApplet *m = new LogitechApplet();

    if (app.isSessionRestored())
    {
        RESTORE(LogitechApplet);
    }else{
        m->show();
    }

    return app.exec();

}
