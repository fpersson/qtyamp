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
 Copyright (C) 2013 - 2016, Fredrik Persson <fpersson.se@gmail.com>
 */
namespace utils{

void FQLog::setLevel(const int &level){
    m_level.setBit(level);
}

void FQLog::disableLevel(const int &level){
    m_level.clearBit(level);
}

void FQLog::clearAllLevels(){
    m_level.clear();
    m_level.resize(LOG::numLevels);
}

void FQLog::info(const QString &tag, const QString &msg){
    if(m_level.testBit(LOG::ALL) || m_level.testBit(LOG::INFO) ){
        QString dbgmsg = "I [";
        dbgmsg.append(getTimeStamp()).append("] ").append(tag).append(" - ").append(msg);

        if(m_debug){
            qDebug() << dbgmsg;
        }
        writeLog(dbgmsg);
    }
}

void FQLog::error(const QString &tag, const QString &msg){
    if(m_level.testBit(LOG::ALL) || m_level.testBit(LOG::ERROR) ){
        QString dbgmsg = "E [";
        dbgmsg.append(getTimeStamp()).append("] ").append(tag).append(" - ").append(msg);
        if(m_debug){
            qDebug() << dbgmsg;
        }
        writeLog(dbgmsg);
    }
}

void FQLog::warning(const QString &tag, const QString &msg){
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

void FQLog::init(const QString &dir, const QString &file, const bool &debugmode){
    m_debug = debugmode;
    m_numLogs = 5;
    setStaleLockTime(STALE_LOCK_TIME);
    QString path;

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
    if(m_lockfile->tryLock()) {
        if (file.open(QFile::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << msg;
            file.close();
        }
        m_lockfile->unlock();
    }

    QFileInfo fileInfo(m_logfile);
    //rotate at 2mb
    if(fileInfo.size()/MEGABYTE > 2){
        rotateLog();
    }
}

void FQLog::rotateLog(){
    if(m_lockfile->tryLock()) {
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
        m_lockfile->unlock();
    }
}

void FQLog::moveLog(QString srcfile, const QString &destfile){
    srcfile = QDir::toNativeSeparators(srcfile);
    QFile file(srcfile);
    if(file.exists()){
        file.rename(destfile);
    }
}

void FQLog::setStaleLockTime(int staleLockTime) {
    if(m_lockfile != NULL) {
        m_lockfile->setStaleLockTime(staleLockTime);
    }
}

FQLog::FQLog(){
    m_level.resize(LOG::numLevels);
    m_level.setBit(LOG::ALL);
    m_lockfile = new QLockFile("DEFAULT_LOCK_FILE");
}

FQLog::~FQLog() {
    delete m_lockfile;
}

}//namespace
