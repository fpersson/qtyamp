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
    Copyright (C) 2013 - 2017, Fredrik Persson <fpersson.se@gmail.com>
 */

#ifndef QTYAMP_PATHMANAGER_H
#define QTYAMP_PATHMANAGER_H

#include <QString>
#include <QDir>
#include <QDebug>

namespace misc {
    class PathManager {
    public:

        static PathManager& getInstance(){
            static PathManager instance;
            return instance;
        }

        void init(const QString& basepath);

        QString getBasePath(){ return QDir::toNativeSeparators(m_basePath); }
        QString getLogDir(){ return QDir::toNativeSeparators(QString("%1%2").arg(m_basePath).arg(LOG_DIR)); }
        QString getTmpDir(){ return QDir::toNativeSeparators(QString("%1%2").arg(m_basePath).arg(TMP_DIR)); }


    private:
        PathManager(){;}
        void createIfNeeded();
        void cleanTmpDir();

        QString m_basePath;
        QString LOG_DIR = "/log";
        QString TMP_DIR = "/tmp";
    };
};

#endif //QTYAMP_PATHMANAGER_H
