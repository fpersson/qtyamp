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
    Copyright (C) 2013, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QBitArray>


namespace utils{

unsigned const int MEGABYTE = 1048576; //Mebibyte

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
    /**
     * @brief init call init before using the log.
     * @param dir
     * @param file
     */
    void init(QString dir, QString file, bool debugmode);

    /**
     * @brief info
     * @param tag
     * @param msg
     */
    void info(QString tag, QString msg);

    /**
     * @brief error
     * @param tag
     * @param msg
     */
    void error(QString tag, QString msg);

    /**
     * @brief warning
     * @param tag
     * @param msg
     */
    void warning(QString tag, QString msg);

    /**
     * @brief setLevel
     * @param level as utils::LOG::ERROR
     */
    void setLevel(int level);

    /**
     * @brief disableLevel
     * @param level as utils::LOG::ERROR
     */
    void disableLevel(int level);

private:
    FQLog();
    void writeLog(QString msg);
    void rotateLog();
    void moveLog(QString srcfile, QString destfile);

    QString getTimeStamp();
    QString m_logdir;
    QString m_logfile;
    QBitArray m_level;

    int m_numLogs;
    bool m_debug;
};

} //namespace

#endif // FLOG_H
