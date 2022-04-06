#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent) {
    m_showDate = true;
}

Logger::Logger(QString fileName, QObject *parent) : QObject(parent) {
    m_showDate = true;
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::write(const QString &value) {
    if (file != nullptr) {
        QString text = value;
        if (m_showDate)
            text = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + text;

        QTextStream out(file);
        out.setCodec("UTF-8");
        out << text << '\n' << Qt::flush;
    }
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}

void Logger::open(QString fileName) {
    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileName);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::close(void) {
    if (file != nullptr) {
        file->close();
        delete file;
    }
    file = nullptr;
}

Logger::~Logger() {
    if (file != nullptr)
        file->close();
}
