#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger : public QObject
{
Q_OBJECT

public:
    explicit Logger(QObject *parent=0);
    explicit Logger(QString fileName, QObject *parent=0);
    ~Logger();
    void setShowDateTime(bool value);
    void close(void);
    void open(QString fileName);

private:
    QFile *file = nullptr;
    bool m_showDate;

public slots:
    void write(const QString &value);
};

extern Logger logger;

#endif // LOGGER_H
