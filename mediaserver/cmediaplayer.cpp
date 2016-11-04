#include "cmediaplayer.h"

CMediaPlayer::CMediaPlayer(QObject *parent) : QObject(parent) {
    m_player = new QMediaPlayer();
    m_playlist = new QMediaPlaylist();
    QString path;
#ifdef Q_OS_ANDROID
    path.append("/mnt/sdcard");
#else
    path.append(QDir::homePath());
#endif
    path.append("/.qtyamp");

    m_flagHandler.setBasePath(path);

    connect(m_playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(changedMedia(int)));
    connect(m_playlist, SIGNAL(currentIndexChanged(int)), parent, SLOT(broadcast()));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(m_player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError(QMediaPlayer::Error)));
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

void CMediaPlayer::fromlast(){
    m_player->stop();
    m_playlist->setCurrentIndex(getLastPlayedTrack());
    m_player->play();
}

void CMediaPlayer::handleError(QMediaPlayer::Error error){
    if(error == QMediaPlayer::ResourceError){
        utils::FQLog::getInstance().info("Debug", "Error code: QMediaPlayer::ResourceError");
        int track = m_playlist->currentIndex();
        m_player->stop();
        m_playlist->nextIndex();
        m_playlist->removeMedia(track);
        m_player->play();
    }else{
        utils::FQLog::getInstance().info("Debug", "Error code: "+QString::number(error));
    }
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
      utils::FQLog::getInstance().info("Debug","Restarting playlist [OK]");
      m_playlist->setCurrentIndex(0);
      m_player->play();
  }
}

void CMediaPlayer::changedMedia(int val){
  utils::FQLog::getInstance().info("Debug","New media ("+QString::number(val)+") [Ok]");
  if(m_player->state() == QMediaPlayer::PlayingState){
      utils::FQLog::getInstance().info("Debug", "m_player state is PlaingState");
      setLastPlayedTrack(val);
  }
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
        utils::FQLog::getInstance().info("Debug", pl+" [Ok]");
    }else{
        utils::FQLog::getInstance().info("Debug", pl+" [Failed]");
    }
}

int CMediaPlayer::getLastPlayedTrack(){
    int retval =0;
    QString value = m_flagHandler.readFile("/last_track");
    if(value!=""){
        retval = value.toInt();
    }
    return retval;
}

void CMediaPlayer::setLastPlayedTrack(int track){
    m_flagHandler.writeFile("/last_track", QString::number(track) , true);
}

QString CMediaPlayer::getVolume(){
    QString retval;
    retval.append("volume=");
    retval.append(QString::number(m_player->volume()));
    retval.append("\r\n");
    return retval;
}

/**
 * @brief CMediaPlayer::setVolume
 * @param vol 0-100
 */
void CMediaPlayer::setVolume(int vol){
    if(vol > 100){
        vol = 100;
    }
    if(vol < 0){
        vol = 0;
    }
    m_player->setVolume(vol);
}
