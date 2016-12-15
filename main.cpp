/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2013, Fredrik Persson <fpersson.se@gmail.com>
 */
#ifdef Q_OS_ANDROID
    #include <QtGui/QGuiApplication>
    #include "qtquick2applicationviewer.h"
#else
    #include <QCoreApplication>
#endif

#if QT_VERSION >= 0x050200
    #include <QtDebug>
    #include <QCommandLineParser>
#endif

#include "mediaserver/cserver.h"
#include "utils/flog.h"

int main(int argc, char *argv[]){
    bool debug = false;
    QString pl = "";
#ifdef Q_OS_ANDROID
    //GUI to make android happy?
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/untitled/main.qml"));
    viewer.showExpanded();
#else
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("qtyamp");
    #if QT_VERSION >= 0x050200
        QCommandLineParser parser;
        parser.setApplicationDescription("qtyamp, a mp3player...");
        parser.addHelpOption();
        parser.addVersionOption();
        parser.addPositionalArgument("playlist", QCoreApplication::translate("main", "Playlist to play"));

        //use -d --debug
        QCommandLineOption debugMode(QStringList() << "d" << "debug", "Display debug message at runtime qDebug()");
        parser.addOption(debugMode);

        parser.process(app);
        const QStringList args = parser.positionalArguments();

        if(args.size() > 0){
            pl = args.at(0);
        }

        debug = parser.isSet(debugMode);
    #endif
#endif
    utils::FQLog::getInstance().init("/.qtyamp/log", "/messages", debug);
    CServer server(pl);
    return app.exec();
}
