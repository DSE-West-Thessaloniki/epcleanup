#include "cleaner.h"
#include "logger.h"
#include "reader.h"
#include <QCoreApplication>
#include <QSettings>
#include <QTimer>

Logger logger;

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QString path, log;
  QUrl url;
  QSettings *settings;
  QTimer *timer;

  settings = new QSettings("epcleanup.ini", QSettings::IniFormat);
  path = settings->value("path", "").toString();
  url = settings->value("url", "").toUrl();
  log = settings->value("log", "").toString();
  if (log == "1" || log.toLower() == "true") {
    logger.open("epcleanup.log");
  }

  logger.write(QString("Initializing..."));
  logger.write(QString("Path: " + path));
  logger.write(QString("Url: " + url.toString()));
  logger.write(QString("Log: " + log));

  timer = new QTimer();
  timer->start(10000);

  Reader *reader = new Reader(url);
  Cleaner *cleaner = new Cleaner(path);

  QObject::connect(reader, SIGNAL(fileRead(int, QString, uint)), cleaner,
                   SLOT(cleanFile(int, QString, uint)));
  QObject::connect(cleaner, SIGNAL(deleted(int)), reader,
                   SLOT(pushDelete(int)));
  QObject::connect(timer, SIGNAL(timeout()), reader, SLOT(getUpdate()));

  return a.exec();
  logger.write(QString("Program exiting..."));
}
