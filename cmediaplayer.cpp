#include "cmediaplayer.h"

CMediaPlayer::CMediaPlayer(QObject *parent) : QObject(parent) {
    m_player = new QMediaPlayer();
    m_playlist = new QMediaPlaylist();
    connect(m_playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(changedMedia(int)));
    connect(m_playlist, SIGNAL(currentIndexChanged(int)), parent, SLOT(broadcast()));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
}

CMediaPlayer::~CMediaPlayer(){
    delete m_player;
    delete m_playlist;
}

void CMediaPlayer::playback(){
    m_player->play();
}

void CMediaPlayer::stopPlayback(){
    m_player->stop();
    m_playlist->setCurrentIndex(0);
}

void CMediaPlayer::next(){
    m_playlist->next();
}

void CMediaPlayer::prev(){
    m_playlist->previous();
}

QString CMediaPlayer::getCurrentTrack(){
    QString retval;
    if (m_player->isMetaDataAvailable()) {
        retval.append(m_player->metaData(QMediaMetaData::AlbumArtist).toString());
        retval.append(" - ");
        retval.append(m_player->metaData(QMediaMetaData::Title).toString());
    }else{
        retval = "N/A";
    }
    retval.append("\r\n");

    return retval;
}

void CMediaPlayer::shuffle(){
    m_player->stop();
    m_playlist->shuffle();
    m_playlist->setCurrentIndex(0);
    m_player->play();
}

/**
 * @brief CMediaPlayer::stateChanged the player will continue to play forever or until stop command is sent.
 * @param state
 */
void CMediaPlayer::stateChanged(QMediaPlayer::State state){
  if((state == QMediaPlayer::StoppedState) && (m_playlist->currentIndex() == -1)){
      qDebug() << "Restarting playlist [OK]";
      m_playlist->setCurrentIndex(0);
      m_player->play();
  }
}

void CMediaPlayer::changedMedia(int val){
  qDebug() << "New media (" << val << ") [Ok]";
}

/**
 * @brief CMediaPlayer::setPlaylist the playlist is just a simple textfile with the absolute path to the song.
 * @param pl
 */
void CMediaPlayer::setPlaylist(QString pl){
    QFile playListFile(pl);

    if(playListFile.open(QIODevice::ReadOnly)){
        QTextStream in(&playListFile);
        while(!in.atEnd()){
            QString instring = in.readLine();
            QFile song(instring);
            m_playlist->addMedia(QUrl::fromLocalFile(song.fileName()));
        }
        m_playlist->setCurrentIndex(0);
        m_player->setPlaylist(m_playlist);
        qDebug() << pl << " [Ok]";
    }else{
        qDebug() << pl << " [Failed]";
    }
}

