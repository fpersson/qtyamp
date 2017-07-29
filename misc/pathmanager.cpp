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

#include "pathmanager.h"

namespace misc{

    void PathManager::init(const QString &basepath) {
        m_basePath = basepath;
        createIfNeeded();
    }

    void PathManager::cleanTmpDir() {
        QDir dir(getTmpDir());
        if(dir.exists()) {
            dir.removeRecursively();
        }
    }

    void PathManager::createIfNeeded() {
        QDir basedir(getBasePath());
        QDir logdir(getLogDir());
        QDir tmpdir(getTmpDir());

        cleanTmpDir();

        if(!basedir.exists()){
            if(!basedir.mkpath(getBasePath())){
                qDebug() << "Could not create: " << getBasePath();
            }
        }

        if(!logdir.exists()){
            if(!logdir.mkpath(getLogDir())){
                qDebug() << "Could not create: " << getLogDir();
            }
        }

        if(!tmpdir.exists()){
            if(!tmpdir.mkpath(getTmpDir())){
                qDebug() << "Could not create: " << getTmpDir();
            }
        }
    }
}
