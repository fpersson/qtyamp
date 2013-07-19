#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ConfigReader
{
public:
    ConfigReader();
    int getTcpPort();

private:
    void createDefaultSettings();
    void writeFile(QString filename, QString value);
    QString readFile(QString filename);
    QString m_configpath;
};

#endif // CONFIGREADER_H
