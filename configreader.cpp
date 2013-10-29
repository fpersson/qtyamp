#include "configreader.h"

ConfigReader::ConfigReader(){
    QString path;
#ifdef Q_OS_ANDROID
    path.append("/mnt/sdcard");
#else
    path.append(QDir::homePath());
#endif
    path.append("/.qtyamp");

    m_flagHandler.setBasePath(path);
    createDefaultSettings(path);
}

void ConfigReader::createDefaultSettings(QString path){
    QDir dir(path);
    if(!dir.exists()){
        if(dir.mkpath(path)){
            utils::FQLog::getInstance().info("Debug", "creating "+path+" [Ok]" );
        }else{
            utils::FQLog::getInstance().info("Debug", "creating "+path+" [Failed]" );
        }
    }else{
        utils::FQLog::getInstance().info("Debug", path+" [Ok]" );
    }
    m_flagHandler.writeFile("/tcp_port", "1234", false);
}


int ConfigReader::getTcpPort(){
    return m_flagHandler.readFile("/tcp_port").toInt();
}
