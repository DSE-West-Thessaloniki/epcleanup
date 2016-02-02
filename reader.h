#ifndef READER_H
#define READER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QUrl url, QObject *parent = 0);

signals:
    void fileRead(int, QString, int);

public slots:
    void replyFinished(QNetworkReply*);
    void getUpdate(void);
    void pushDelete(int);

private:
    QUrl url;
    QNetworkAccessManager *networkManager;
};

#endif // READER_H
