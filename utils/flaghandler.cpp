#include "flaghandler.h"

namespace utils{

void FlagHandler::setBasePath(QString basePath){
    m_basePath = QDir::toNativeSeparators(basePath);
}

QString FlagHandler::readFile(QString filename){
    QString ret = "";
    QString path = m_basePath;
    path.append(filename);
    path = QDir::toNativeSeparators(path);

    QFile file(path);
    if(file.exists()){
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ts(&file);
        ret = ts.readLine().trimmed();
    }else{
        utils::FQLog::getInstance().info("Debug", path+" [Failed]");
    }
    return ret;
}

void FlagHandler::writeFile(QString filename, QString value, bool update){
    QString path = m_basePath;
    path.append(filename);
    path = QDir::toNativeSeparators(path);
    QFile file(path);
    if(!file.exists() && !update){
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << value;
        file.close();
    }else if (update) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << value;
        file.close();
    }
}

}//namespace
