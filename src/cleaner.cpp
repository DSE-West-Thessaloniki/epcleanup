#include "cleaner.h"
#include "logger.h"

extern Logger logger;

Cleaner::Cleaner(QString path, QObject *parent) : QObject(parent)
{
    this->path.setPath(path);
}

void Cleaner::cleanFile(int id, QString filename, uint timestamp)
{
    if (id) { // id cannot be zero
        if (!(filename.isEmpty() || filename.isNull())) {
            QString tmp;
            bool result;

            logger.write(QString("Search for file ") + filename);
            tmp = findFile(path, filename);
            if (!(tmp.isNull() || tmp.isNull())) {
                result = QFile::remove(tmp);
                logger.write(QString("Remove file ") + tmp + ". Result: " + (result?"true":"false"));
                if (result)
                    emit deleted(id);
            }
            else {
                logger.write(QString("Not found!"));
            }
        }
        else {
            logger.write(QString("Invalid filename of ") + filename);
        }
    }
    else {
        logger.write(QString("Invalid id of ") + QString::number(id));
    }
}

QString Cleaner::findFile(QDir dir, QString filename)
{
    QStringList dirs;

    if (QFile::exists(dir.canonicalPath() + "/" + filename))
        return QString(dir.canonicalPath() + "/" + filename);
    else { // file not in this dir, search recursively
        dirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for (int i=0; i<dirs.size(); i++) {
            QString tmp;
            tmp = findFile(QDir(dir.canonicalPath() + "/" + dirs[i]), filename);
            if (!(tmp.isNull() || tmp.isEmpty())) {
                return QString(tmp);
            }
        }
        return(QString());
    }
}
