#ifndef FLOG_H
#define FLOG_H

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
    Copyright (C) 2013 - 2016, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QBitArray>
#include <QLockFile>
#include <QtCore/QPointer>


namespace utils{

unsigned const int MEGABYTE = 1048576; //Mebibyte
const int STALE_LOCK_TIME = 250; //in ms, used to override QLockFile stale time, qt default is 30s

#ifdef Q_OS_LINUX
    const QString DEFAULT_LOCK_FILE = "/var/lock/fqlog.lock";
#else
    const QString DEFAULT_LOCK_FILE = "fqlog.lock";
#endif

enum LOG{
    ERROR,
    WARNING,
    INFO,
    ALL,
    numLevels
};

/**
 * @brief The FQLog class - a c++ 11 thread safe logger.
 */
class FQLog
{
public:
    static FQLog& getInstance(){
        static FQLog instance;
        return instance;
    }

    ~FQLog();
    /**
     * @brief init call init before using the log.
     * @param dir
     * @param file
     */
    void init(const QString &dir, const QString &file, const bool &debugmode);

    /**
     * @brief info
     * @param tag
     * @param msg
     */
    void info(const QString &tag, const QString &msg);

    /**
     * @brief error
     * @param tag
     * @param msg
     */
    void error(const QString &tag, const QString &msg);

    /**
     * @brief warning
     * @param tag
     * @param msg
     */
    void warning(const QString &tag, const QString &msg);

    /**
     * @brief setLevel
     * @param level as utils::LOG::ERROR
     */
    void setLevel(const int &level);

    /**
     * @brief disableLevel
     * @param level as utils::LOG::ERROR
     */
    void disableLevel(const int &level);

    void clearAllLevels();

    /**
     * set stale lock time, default is 250ms
     * @param staleLockTime
     */
    void setStaleLockTime(int staleLockTime);

private:
    FQLog();
    void writeLog(QString msg);
    void rotateLog();
    void moveLog(QString srcfile, const QString &destfile);

    QString getTimeStamp();
    QString m_logdir;
    QString m_logfile;
    QBitArray m_level;

    QLockFile *m_lockfile;

    int m_numLogs;
    bool m_debug;
};

} //namespace

#endif // FLOG_H
