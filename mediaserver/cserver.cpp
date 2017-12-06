#include "cserver.h"

CServer::CServer(const QString& settings, QString playlist, QObject *parent) : QObject(parent){
    m_tcpserver = new QTcpServer(this);
    m_mediaplayer = new CMediaPlayer(this);
    m_localServer = new QLocalServer(this);

    if(!m_localServer->listen("qtyamp.getTrack")){
        utils::FQLog::getInstance().info("Debug", "Error: "+m_localServer->errorString());
        m_localServer->close();
    }

    m_playlistLoaded = false;

    QString settinfsfile( QString("%1%2").arg(misc::PathManager::getInstance().getBasePath()).arg(settings) );
    m_settings = new QSettings(settinfsfile, QSettings::IniFormat);

    QString pl_path;

#ifdef Q_OS_ANDROID
    pl_path = "/mnt/sdcard";
#else
    if(playlist.isEmpty()){
        pl_path = QDir::homePath();
    }
#endif
    if(playlist.isEmpty()){
        pl_path.append("/playlist");
    }else{
        pl_path = playlist;
    }
    utils::FQLog::getInstance().info("Debug", "playlist: "+pl_path);
    pl_path = QDir::toNativeSeparators(pl_path);


    if(QFile::exists(pl_path)){
        m_mediaplayer->setPlaylist(pl_path);
        m_playlistLoaded = true;
    }else{
        utils::FQLog::getInstance().info("Debug", pl_path+" not found");
    }


    connect(m_tcpserver, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(m_localServer, SIGNAL(newConnection()), this, SLOT(getTrack()));

    m_settings->beginGroup("Network");

    qint64 tcpport = m_settings->value("tcp_port", 1024).toInt();

    if(!m_tcpserver->listen(QHostAddress::Any, tcpport)){
        utils::FQLog::getInstance().info("Debug", "Server [Failed]");
    }else{
        utils::FQLog::getInstance().info("Debug", "Server [Ok]");
    }

    m_settings->endGroup();
}

CServer::~CServer(){
    delete m_settings;
    delete m_tcpserver;
    //delete m_udpBroadcast;
    delete m_mediaplayer;
    //delete m_broadcastTimer;
    delete m_localServer;
}

void CServer::newConnection(){
    m_socket = m_tcpserver->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(startRead()));

    if(m_playlistLoaded){
        m_socket->write("Welcome to my musicplayer!\r\nValid commads are start|stop|shuffle|next|prev|gettrack|continue|getvolume|playdir\r\nEnter command: ");
    }else{
        m_socket->write("Welcome to my musicplayer!\r\nNo playlist found....");
    }
    m_socket->flush();
}

void CServer::getTrack() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << m_mediaplayer->getCurrentTrack().toStdString().c_str();

    QLocalSocket *localSocket = m_localServer->nextPendingConnection();
    connect(localSocket, SIGNAL(disconnected()), localSocket, SLOT(deleteLater()));

    localSocket->write(block);
    localSocket->flush();
    localSocket->disconnectFromServer();
}

void CServer::startRead(){
    char buffer[1024] = {0};
    m_socket->read(buffer, m_socket->bytesAvailable());
    QString msg(buffer);
    utils::FQLog::getInstance().info("Debug", msg.trimmed());
    if(msg.trimmed() == "stop"){
        m_socket->write("Stop playback!\r\n");
        m_mediaplayer->stopPlayback();
    }else if(msg.trimmed()== "start"){
        m_socket->write("Start playback!\r\n");
        m_mediaplayer->playback();
    }else if(msg.trimmed() == "shuffle"){
        m_socket->write("Shuffle!\r\n");
        m_mediaplayer->shuffle();
    }else if(msg.trimmed() == "next"){
        m_socket->write("next!\r\n");
        m_mediaplayer->next();
    }else if(msg.trimmed() == "prev"){
        m_socket->write("prev!\r\n");
        m_mediaplayer->prev();
    }else if(msg.trimmed() == "gettrack"){
        m_socket->write(m_mediaplayer->getCurrentTrack().toStdString().c_str());
    }else if(msg.trimmed() == "continue") {
        m_socket->write("continue!\r\n");
        m_mediaplayer->fromlast();
    }else if(msg.trimmed() == "playdir"){
        m_socket->write("playdir!\r\n");
        m_mediaplayer->stopPlayback();

        m_settings->beginGroup("Storage");

        QString external = QDir::toNativeSeparators(m_settings->value("external").toString());

        if(QFile::exists(external)){
            QStringList filter(".mp3");
            PlaylistGenerator playlistGenerator;
            QStringList tmpPl = playlistGenerator.listFiles(external, filter);
            m_mediaplayer->setPlaylist(tmpPl);
            m_playlistLoaded = true;
            utils::FQLog::getInstance().info("Debug", QString("%1 %2").arg(external).arg("found."));
        }else{
            utils::FQLog::getInstance().info("Debug", QString("%1 %2").arg(external).arg("not found."));
        }

        m_mediaplayer->playback();
    }else if(msg.trimmed() == "getvolume"){
        m_socket->write(m_mediaplayer->getVolume().toStdString().c_str());
    }else{
        Command cmd;
        if(m_commandParser.parse(msg.trimmed(), "=", cmd)){
            if(cmd.cmd=="setvolume"){
                utils::FQLog::getInstance().info("Debug", "Requested volume is "+cmd.value);
                m_socket->write("change volume!\r\n");
                m_mediaplayer->setVolume(cmd.value.toInt());
            }
        }else{
            m_socket->write("Please consult the source code or your brain doctor\r\n");
        }
    }
    m_socket->flush();
    m_socket->waitForBytesWritten(3000);

    m_socket->close();
}

