#include "cserver.h"

CServer::CServer(QObject *parent) : QObject(parent){
    m_tcpserver = new QTcpServer(this);
    m_udpBroadcast = new QUdpSocket(this);
    m_mediaplayer = new CMediaPlayer(this);
    m_broadcastTimer = new QTimer();
    m_mediaplayer->setPlaylist("/home/fredrik/playlist");


    connect(m_tcpserver, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(m_broadcastTimer, SIGNAL(timeout()), this, SLOT(braodcastDelayed()));

    if(!m_tcpserver->listen(QHostAddress::Any, 1234)){
        qDebug() << "Could not start server.";
    }else{
        qDebug() << "Server is upp and running...";
    }
}

void CServer::newConnection(){
    m_socket = m_tcpserver->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(startRead()));

    m_socket->write("Welcome to my musicplayer!\r\nValid commads are start|stop|shuffle|next|prev|gettrack\r\nEnter command: ");
    m_socket->flush();
}

void CServer::broadcast(int val){
    qDebug() << "Should broadcast...";
    m_broadcastTimer->start(10000); //10s
}

void CServer::braodcastDelayed(){
    QByteArray datagram = m_mediaplayer->getCurrentTrack().toStdString().c_str();
    m_udpBroadcast->writeDatagram(datagram.data(), datagram.size(),QHostAddress::Broadcast, 5007);
    m_broadcastTimer->stop();
}

void CServer::startRead(){
    char buffer[1024] = {0};
    m_socket->read(buffer, m_socket->bytesAvailable());
    QString msg(buffer);
    qDebug() << msg.trimmed();
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
    }else{
        m_socket->write("Please consult the source code or your brain doctor\r\n");
    }
    m_socket->flush();
    m_socket->waitForBytesWritten(3000);

    m_socket->close();
}

