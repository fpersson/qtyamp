//
// Created by fredrik on 2017-07-29.
//

#ifndef QTYAMP_DEFAULTSETTINGS_H
#define QTYAMP_DEFAULTSETTINGS_H

#include <QSettings>
#include <QFile>

namespace misc {
    class DefaultSettings {
    public:
        DefaultSettings(const QString& path, const QString& file);
    };
};


#endif //QTYAMP_DEFAULTSETTINGS_H
