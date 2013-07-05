#include "cmediaplayer.h"

CMediaPlayer::CMediaPlayer(QObject *parent) : QObject(parent) {
    m_player = new QMediaPlayer();
    m_playlist = new QMediaPlaylist();
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(positonChanged(qint64)));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(m_playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(changedMedia(int)));
}

CMediaPlayer::~CMediaPlayer(){
    delete m_player;
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

void CMediaPlayer::positonChanged(qint64 val){
  //qDebug() << "val=" << val;
}

/**
 * @brief CMediaPlayer::stateChanged the player will contionu to play forever or until stop command is sent.
 * @param state
 */
void CMediaPlayer::stateChanged(QMediaPlayer::State state){
  qDebug() << "state=" << state;
  if((state == QMediaPlayer::StoppedState) && (m_playlist->currentIndex() == -1)){
      qDebug() << "This is the end of the line, will restart";
      m_playlist->setCurrentIndex(0);
      m_player->play();
  }
}

void CMediaPlayer::changedMedia(int val){
  qDebug() << "changed media (" << val << ")";
}

/**
 * @brief CMediaPlayer::setPlaylist the playlist is just a simple textfile with the absolute path to the song.
 * @param pl
 */
void CMediaPlayer::setPlaylist(QString pl){
    QFile playListFile(pl);

    if(playListFile.open(QIODevice::ReadOnly)){
        QTextStream in(&playListFile);
        qDebug() << "Reading " << pl;
        while(!in.atEnd()){
            QString instring = in.readLine();
            QFile song(instring);
            m_playlist->addMedia(QUrl::fromLocalFile(song.fileName()));
        }
        m_playlist->setCurrentIndex(0);
        m_player->setPlaylist(m_playlist);
    }else{
        qDebug() << pl << " not found.";
    }
}

