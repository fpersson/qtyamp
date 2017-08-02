//
// Created by fredrik on 2017-07-29.
//

#include "defaultsettings.h"

namespace misc {

    DefaultSettings::DefaultSettings(const QString &path, const QString &file) {
        QString settingsfile = QString("%1%2").arg(path).arg(file);
        QFile qFile(settingsfile);
        if(!qFile.exists()) {
            QSettings *settings = new QSettings(settingsfile, QSettings::IniFormat);

            settings->beginGroup("Network");
            settings->setValue("tcp_port", 1234);
            settings->setValue("udp_broadcast", true);
            settings->endGroup();

            settings->beginGroup("Playlist");
            settings->setValue("playlist", "/path/to/playlist");
            settings->setValue("last_track", 0);
            settings->setValue("shuffle", true);
            settings->setValue("volume", 100);
            settings->endGroup();

            delete settings;
        }
    }
} //namespace
