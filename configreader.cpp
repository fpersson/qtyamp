#include "configreader.h"

ConfigReader::ConfigReader(){
    m_configpath.append(QDir::homePath());
    m_configpath.append("/.qtyamp");

    createDefaultSettings();
}

QString ConfigReader::readFile(QString filename){
    QString ret = "";
    QString path = m_configpath;
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

void ConfigReader::writeFile(QString filename, QString value){
    QString path = m_configpath;
    path.append(filename);
    path = QDir::toNativeSeparators(path);
    QFile file(path);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << value;
        file.close();
    }
}

void ConfigReader::createDefaultSettings(){
    QDir dir(m_configpath);
    if(!dir.exists()){
        dir.mkdir(m_configpath);
        //qDebug() << "creating " << m_configpath << "[Ok]";
        utils::FQLog::getInstance().info("Debug", "creating "+m_configpath+" [Ok]" );
    }else{
        //qDebug() << m_configpath << " [Ok]";
        utils::FQLog::getInstance().info("Debug", m_configpath+" [Ok]" );
    }
    writeFile("/tcp_port", "1234");
}

int ConfigReader::getTcpPort(){
    return readFile("/tcp_port").toInt();
}
