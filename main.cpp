#include <QCoreApplication>
#include <QSettings>
#include <QTimer>
#include "reader.h"
#include "cleaner.h"
#include "logger.h"

Logger logger("epcleanup.log");

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path;
    QUrl url;
    QSettings *settings;
    QTimer *timer;

    logger.write(QString("Initializing..."));
    settings = new QSettings("epcleanup.ini", QSettings::IniFormat);
    path = settings->value("path", "").toString();
    logger.write(QString("Path: " + path));
    url = settings->value("url", "").toUrl();
    logger.write(QString("Url: " + url.toString()));

    timer = new QTimer();
    timer->start(1000);

    Reader *reader = new Reader(url);
    Cleaner *cleaner = new Cleaner(path);

    QObject::connect(reader, SIGNAL(fileRead(int,QString,int)),
                     cleaner, SLOT(cleanFile(int,QString,uint)));
    QObject::connect(timer, SIGNAL(timeout()),
                     reader, SLOT(getUpdate()));

    return a.exec();
    logger.write(QString("Program exiting..."));
}

