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

#include "cserver.h"
#include "fqlog.h"

int main(int argc, char *argv[]){
#ifdef Q_OS_ANDROID
    //GUI to make android happy?
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/untitled/main.qml"));
    viewer.showExpanded();
#else
    QCoreApplication app(argc, argv);
#endif
    utils::FQLog::getInstance().init("/.qtyamp/log", "/messages");
    CServer server;
    return app.exec();
}
