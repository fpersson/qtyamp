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

#include "pidwriter.h"
#include "flog.h"

utils::PidWriter::PidWriter(const QString &path, const QString &file, const qint64 &pid) {
    write(path, file, pid);
}

void utils::PidWriter::write(const QString &path, const QString &file, const qint64 &pid) {

    utils::FQLog::getInstance().info("UTILS", QString("[PidWriter::write] Pid:%1").arg(QString::number(pid)));
    QFile pidfile(QString("%1%2%3").arg(QDir::homePath()).arg(path).arg(file));

    if(pidfile.open(QIODevice::WriteOnly)){
        QTextStream out(&pidfile);
        out << pid;
        pidfile.close();
    }else{
        utils::FQLog::getInstance().info("UTILS", QString("[PidWriter::write] could not write to: %1%2%3 (pid: %4)")
                                                    .arg(QDir::homePath())
                                                    .arg(path)
                                                    .arg(file)
                                                    .arg(QString::number(pid)));
    }
}
