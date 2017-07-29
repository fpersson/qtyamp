#include <QTest>
#include <QDebug>
#include <QDir>
#include "utils/flog.h"
#include "misc/pathmanager.h"
#include "mediaserver/playlistgenerator.h"

QString SUB_DATADIR1 = "/dir1";
QString SUB_DATADIR12 = "/dir1/dir2";
QString SUB_DATADIR2 = "/dir2";

class UnitTest : public QObject{
    Q_OBJECT
public:
    UnitTest();
    ~UnitTest();
private slots:
    void playlistTest();
    void PathManagerInitTest();

private:
    QString m_testdir;
    QString m_testdatadir;
};

UnitTest::UnitTest() {
    //setupt testdir in /tmp
    QString path;
    path = QDir::homePath();
    path.append("/qtymp_unittest");

    m_testdir = QDir::toNativeSeparators(path);
    utils::FQLog::getInstance().init(m_testdir, "/messages", true);

    m_testdatadir=m_testdir+SUB_DATADIR1;
    QDir datadir;
    datadir.mkdir(m_testdir);

    for(int i=0; i<3; i++){
        QString newfilename = QString("%1/foo0%2.txt").arg(m_testdir).arg(QString::number(i));
        QFile file(newfilename);
        if(file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream << "." << endl;
        }
    }

    QDir subdir;
    subdir.mkdir(m_testdatadir);

    for(int i=0; i<3; i++){
        QString newfilename = QString("%1/foo0%2.txt").arg(m_testdatadir).arg(QString::number(i));
        QFile file(newfilename);
        if(file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream << "." << endl;
        }
    }

}

UnitTest::~UnitTest() {
    QDir dir(m_testdir);
    dir.removeRecursively();
}

void UnitTest::playlistTest() {
    PlaylistGenerator pg;
    QStringList filter(".txt");
    QStringList playlist = pg.listFiles(m_testdir, filter );
    QCOMPARE(6, playlist.size());
    //Qt QDirIterator is listing files as foo01 foo02 and foo00
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdir).arg(QString::number(1)), playlist.at(0));
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdir).arg(QString::number(2)), playlist.at(1));
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdir).arg(QString::number(0)), playlist.at(2));
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdatadir).arg(QString::number(1)), playlist.at(3));
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdatadir).arg(QString::number(2)), playlist.at(4));
    QCOMPARE(QString("%1/foo0%2.txt").arg(m_testdatadir).arg(QString::number(0)), playlist.at(5));
}

void UnitTest::PathManagerInitTest(){
    QString baseDir;
    baseDir = QDir::homePath();
    baseDir.append("/qtymp_unittest");

    misc::PathManager::getInstance().init(baseDir);
    QCOMPARE(misc::PathManager::getInstance().getBasePath(), baseDir);
    QCOMPARE(misc::PathManager::getInstance().getLogDir(), QString("%1%2").arg(baseDir).arg("/log"));
    QCOMPARE(misc::PathManager::getInstance().getTmpDir(), QString("%1%2").arg(baseDir).arg("/tmp"));

    QDir checkDir(baseDir);

    QVERIFY(checkDir.exists(misc::PathManager::getInstance().getBasePath()));
    QVERIFY(checkDir.exists(misc::PathManager::getInstance().getTmpDir()));
    QVERIFY(checkDir.exists(misc::PathManager::getInstance().getLogDir()));

}

QTEST_MAIN(UnitTest)
#include "testmain.moc"
