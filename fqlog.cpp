#include "fqlog.h"
namespace utils{

void FQLog::info(QString tag, QString msg){
    QString timestamp = QDateTime::currentDateTime().toString("yyMMdd - hh:mm:ss");
    QString dbgmsg = "I [";
    dbgmsg.append(timestamp).append("] ").append(tag).append(" - ").append(msg);
    if(m_debug){
        qDebug() << dbgmsg; //realtime monitoring ;)
    }
    writeLog(dbgmsg);
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
    if(file.open(QFile::Append | QIODevice::Text)){
        QTextStream out(&file);
        out << msg;
        file.close();
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

}//namespace
