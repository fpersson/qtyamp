#include "configreader.h"

ConfigReader::ConfigReader(){
    QString path;
    path.append(QDir::homePath());
    path.append("/.qtyamp");

    m_flagHandler.setBasePath(path);
    createDefaultSettings(path);
}

void ConfigReader::createDefaultSettings(QString path){
    QDir dir(path);
    if(!dir.exists()){
        dir.mkdir(path);
        utils::FQLog::getInstance().info("Debug", "creating "+path+" [Ok]" );
    }else{
        utils::FQLog::getInstance().info("Debug", path+" [Ok]" );
    }
    m_flagHandler.writeFile("/tcp_port", "1234", false);
}


int ConfigReader::getTcpPort(){
    return m_flagHandler.readFile("/tcp_port").toInt();
}
