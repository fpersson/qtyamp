#include "flog.h"
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
 Copyright (C) 2016, Fredrik Persson <fpersson.se@gmail.com>
 */
namespace utils{

void FQLog::setLevel(int level){
    m_level.setBit(level);
}

void FQLog::info(QString tag, QString msg){
    if(m_level.testBit(LOG::ALL) || m_level.testBit(LOG::INFO) ){
        QString dbgmsg = "I [";
        dbgmsg.append(getTimeStamp()).append("] ").append(tag).append(" - ").append(msg);

        if(m_debug){
            qDebug() << dbgmsg; //realtime monitoring ;)
        }
        writeLog(dbgmsg);
    }
}

void FQLog::error(QString tag, QString msg){
    if(m_level.testBit(LOG::ALL) || m_level.testBit(LOG::ERROR) ){
        QString dbgmsg = "E [";
        dbgmsg.append(getTimeStamp()).append("] ").append(tag).append(" - ").append(msg);
        if(m_debug){
            qDebug() << dbgmsg;
        }
        writeLog(dbgmsg);
    }
}

void FQLog::warning(QString tag, QString msg){
    if(m_level.testBit(LOG::ALL) || m_level.testBit(LOG::WARNING) ){
        QString dbgmsg = "W [";
        dbgmsg.append(getTimeStamp()).append("] ").append(tag).append(" - ").append(msg);
        if(m_debug){
            qDebug() << dbgmsg;
        }
        writeLog(dbgmsg);
    }
}

QString FQLog::getTimeStamp(){
    return QDateTime::currentDateTime().toString("yyMMdd - hh:mm:ss");
}

/**
 * @todo check rw permisson for dirs
 */
void FQLog::init(QString dir, QString file, bool debugmode){
    m_debug = debugmode;
    m_numLogs = 5;
    QString path;
#ifdef Q_OS_ANDROID
    path = "/mnt/sdcard";
    qDebug() << "Android";
#else
    path = QDir::homePath();
#endif
    m_logdir = QDir::toNativeSeparators(path.append(dir));
    m_logfile = QDir::toNativeSeparators(path.append(file));
    QDir logdir(m_logdir);
    if(!logdir.exists()){
        if(!logdir.mkpath(m_logdir)){
            qDebug() << "Could not create: " << m_logdir;
        }
    }
    rotateLog();
}

void FQLog::writeLog(QString msg){
    msg.append("\n");
    QFile file(m_logfile);
    QFileInfo fileInfo(m_logfile);
    if(file.open(QFile::Append | QIODevice::Text)){
        QTextStream out(&file);
        out << msg;
        file.close();
    }

    //ca 2mb stora logfiler
    if(fileInfo.size()/MEGABYTE > 2){
        rotateLog();
    }
}

void FQLog::rotateLog(){
    QString srcLog;
    QString destLog;
    QFile log(m_logfile);

    if(log.exists()){
        for(int i = m_numLogs-1; i != 0; --i){
            srcLog = m_logfile;
            destLog = m_logfile;
            srcLog.append(".");
            int l = i -1;
            srcLog.append(QString::number(l));
            destLog.append(".");
            destLog.append(QString::number(i));
            moveLog(srcLog, destLog);
        }
        destLog = m_logfile;
        moveLog(m_logfile, destLog.append(".0"));
        QFile file(m_logfile);
        if(file.exists()){
            file.remove();
        }
    }
}

void FQLog::moveLog(QString srcfile, QString destfile){
    srcfile = QDir::toNativeSeparators(srcfile);
    QFile file(srcfile);
    if(file.exists()){
        file.rename(destfile);
    }
}

FQLog::FQLog(){
    m_level.resize(LOG::numLevels);
    m_level.setBit(LOG::ALL);
}

}//namespace
