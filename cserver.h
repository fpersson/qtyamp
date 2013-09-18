#ifndef CSERVER_H
#define CSERVER_H

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
    Copyright (C) 2013, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>

#include "commandparser.h"
#include "cmediaplayer.h"
#include "configreader.h"
#include "fqlog.h"

class CServer : public QObject
{
    Q_OBJECT
public:
    explicit CServer(QObject *parent = 0);
    ~CServer();

signals:

public slots:
    void newConnection();
    void startRead();
    void broadcast();
    void braodcastDelayed();

private:
    QTcpServer *m_tcpserver;
    QTcpSocket *m_socket;
    QUdpSocket *m_udpBroadcast;
    QTimer *m_broadcastTimer;

    CMediaPlayer *m_mediaplayer;
    ConfigReader m_configReader;
    CommandParser m_commandParser;
};

#endif // CSERVER_H

