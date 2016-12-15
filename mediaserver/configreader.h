#ifndef CONFIGREADER_H
#define CONFIGREADER_H

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

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <utils/flog.h>
#include <utils/flaghandler.h>

class ConfigReader
{
public:
    ConfigReader();
    int getTcpPort();


private:
    void createDefaultSettings(const QString &path);
    utils::FlagHandler m_flagHandler;
};

#endif // CONFIGREADER_H
