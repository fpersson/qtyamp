//
// Created by fredrik on 2017-03-17.
//

#ifndef QTYAMP_PLAYLISTGENERATOR_H
#define QTYAMP_PLAYLISTGENERATOR_H

#include <QtCore/QObject>

class PlaylistGenerator : public QObject {
    Q_OBJECT
public:
    PlaylistGenerator(){;}
    ~PlaylistGenerator(){;}

    QStringList listFiles(const QString &dir, const QStringList &filter);
};


#endif //QTYAMP_PLAYLISTGENERATOR_H
