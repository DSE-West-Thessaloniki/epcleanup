#include "reader.h"
#include "logger.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

extern Logger logger;

Reader::Reader(QUrl url, QObject *parent) : QObject(parent) {
  networkManager = new QNetworkAccessManager();
  this->url = url;
  connect(networkManager, SIGNAL(finished(QNetworkReply *)), this,
          SLOT(replyFinished(QNetworkReply *)));
}

void Reader::replyFinished(QNetworkReply *reply) {
  QJsonDocument jdoc;
  QJsonParseError jerr;
  QJsonObject jobj, jfobj;
  QJsonArray jarray;

  if (reply->error() == QNetworkReply::NoError) {
    jdoc = QJsonDocument::fromJson(reply->readAll(), &jerr);
    if (jerr.error == QJsonParseError::NoError) {
      jobj = jdoc.object();

      // Έλεγχος τιμών
      if (!jobj.value("done").isUndefined()) {
        logger.write(
            QString("File " + jobj.value("done").toString() + " is deleted"));
      } else {
        jarray = jobj.value("files").toArray();
        for (int i = 0; i < jarray.size(); i++) {
          jfobj = jarray[i].toObject();
          logger.write(QString("File to be removed: ") +
                       jfobj.value("fileName").toString());
          emit fileRead(jfobj.value("id").toInt(),
                        jfobj.value("fileName").toString(),
                        (uint)jfobj.value("unixTime").toInt());
        }
      }
    } else {
      logger.write(QString("Json Error: ") + jerr.errorString());
    }
  } else {
    logger.write(QString("Network Error: ") + reply->errorString());
  }
  reply->deleteLater();
}

void Reader::getUpdate(void) { networkManager->get(QNetworkRequest(url)); }

void Reader::pushDelete(int id) {
  networkManager->get(QNetworkRequest(
      QUrl(url.toString() + QString("?del=") + QString::number(id))));
}
