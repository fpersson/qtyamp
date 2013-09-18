#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

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
#include <QStringList>

#include <fqlog.h>

struct Command{
    QString cmd;
    QString value;
};

class CommandParser
{
public:
    CommandParser();
    bool parse(QString string, QString delimiter, Command &cmdOut);
private:
};

#endif // COMMANDPARSER_H
