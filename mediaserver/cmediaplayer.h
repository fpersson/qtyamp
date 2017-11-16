#ifndef CMEDIAPLAYER_H
#define CMEDIAPLAYER_H

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
    Copyright (C) 2013 - 2017 Fredrik Persson <fpersson.se@gmail.com>
 */
#include <QObject>
#include <QMediaPlaylist>
#include <QTextStream>
#include <QtMultimedia/QtMultimedia>
#include <QSettings>

#include "utils/flog.h"
#include "misc/pathmanager.h"

/**
 * @brief The CMediaPlayer class
 */
class CMediaPlayer : public QObject
{
  Q_OBJECT
public:
    explicit CMediaPlayer(QObject *parent = 0);
    ~CMediaPlayer();
    void setPlaylist(const QString &pl);
    void setPlaylist(const QStringList &pl);
    void playback();
    void stopPlayback();
    void shuffle();
    void next();
    void prev();
    void fromlast();
    QString getCurrentTrack();
    QString getVolume();
    void setVolume(int vol);

signals:

public slots:
    void stateChanged(QMediaPlayer::State state);
    void changedMedia(int val);
    void handleError(QMediaPlayer::Error error);

private:
    int getLastPlayedTrack();
    void setLastPlayedTrack(const int &track);

    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QSettings *m_settings;
    //utils::FlagHandler m_flagHandler;
};

#endif // CMEDIAPLAYER_H
