#ifndef CMEDIAPLAYER_H
#define CMEDIAPLAYER_H

#include <QtMultimedia>
#include <QMediaPlaylist>
#include <QtDebug>
#include <QObject>
#include <QTextStream>

/**
 * @brief The CMediaPlayer class
 */
class CMediaPlayer : public QObject
{
  Q_OBJECT
public:
  explicit CMediaPlayer(QObject *parent = 0);
  ~CMediaPlayer();
  void setPlaylist(QString pl);
  void playback();
  void stopPlayback();
  void shuffle();
  void next();
  void prev();
  QString getCurrentTrack();
signals:

public slots:
   void positonChanged(qint64 val);
   void stateChanged(QMediaPlayer::State state);
   void changedMedia(int val);

private:
  QMediaPlayer *m_player;
  QMediaPlaylist *m_playlist;
};

#endif // CMEDIAPLAYER_H
