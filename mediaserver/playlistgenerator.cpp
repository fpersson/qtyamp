//
// Created by fredrik on 2017-03-17.
//

#include <QtCore/QDir>
#include <utils/flog.h>
#include <QtCore/QDirIterator>
#include "playlistgenerator.h"

QStringList PlaylistGenerator::listFiles(const QString &dir, const QStringList &filter) {
    QStringList retList;
    QDir::toNativeSeparators(dir);
    QDir workingdir(dir);

    if(workingdir.exists() && workingdir.isReadable()){
        QDirIterator dirIterator(dir, QDirIterator::Subdirectories);
        while(dirIterator.hasNext()){
            dirIterator.next();
            QFileInfo info = dirIterator.fileInfo();
            for(int j=0; j<filter.size(); j++){
                if(info.fileName().endsWith(filter.at(j))){
                    retList.append(info.absoluteFilePath());
                }
            }
        }
    }else{
        utils::FQLog::getInstance().info("Debug", "Could not read "+dir);
    }

    return retList;
}
