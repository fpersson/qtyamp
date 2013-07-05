#ifndef CSERVER_H
#define CSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "cmediaplayer.h"

class CServer : public QObject
{
    Q_OBJECT
public:
    explicit CServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
    void startRead();

private:
    QTcpServer *m_tcpserver;
    QTcpSocket *m_socket;

    CMediaPlayer *m_mediaplayer;
};

#endif // CSERVER_H

