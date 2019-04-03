#include "connector.h"
#include "ldapobject.h"
#include "ldapconnection.h"
#include "common.h"

#include <QDirIterator>

Connector::Connector(QObject *parent) : QObject(parent), isUpdated(true), temp(new QTemporaryDir)
{
    QDir::setCurrent(temp->path());
}

Connector::~Connector()
{
    disconnect();
}

void Connector::disconnect()
{
    if (adfs.state() == QProcess::NotRunning)
        return;

    QProcess umount;
    qDebug() << "Connector::disconnect: umount " << root;
    umount.start("fusermount", QStringList() << "-u" << root.path());
    if (!umount.waitForFinished(1000)) {
        qDebug() << "Connector::~connect: kill fuserumount";
        umount.kill();
    }
    if(!adfs.waitForFinished(1000)) {
        qDebug() << "Connector::~connect: terminate adfs";
        adfs.terminate();
        if(!adfs.waitForFinished(1000)) {
            qDebug() << "Connector::~connect: kill adfs";
            adfs.kill();
        }
    }
}

bool Connector::connect(QString server)
{
    QStringList mounts = search(server);
    dc = server;

    qDebug() << "Connector::connect: already mounts " << mounts << ", server " << server;
    if (!mounts.empty()) {
        qDebug() << "Connector::connect: connect to already mounted " << mounts.at(0);
        return connect(QDir(mounts.at(0)));
    }

    QDir mountRoot(temp->path() + "/mnt");
    qDebug() << "Connector::connect: mount path: " << mountRoot;
    if (!mountRoot.exists())
        mountRoot.mkpath(mountRoot.path());

    adfs.setStandardOutputFile(QProcess::nullDevice());
    adfs.setStandardErrorFile(QProcess::nullDevice());
//    QObject::connect(&adfs, &QProcess::readyReadStandardError, this, &Connector::readStandardError);
//    QObject::connect(&adfs, &QProcess::readyReadStandardOutput, this, &Connector::readStandardOutput);
//    adfs.setProcessChannelMode(QProcess::ForwardedErrorChannel);
//    adfs.setReadChannel(QProcess::StandardOutput);
    adfs.start("hadfs", QStringList() << mountRoot.path() << server);
    if (!adfs.waitForStarted(3000)) {
        qDebug() << "Connector::connect: adfs not started: " << adfs.errorString();
        adfs.kill();
        return false;
    }

    mounts = search(server);
    qDebug() << "Connector::connect: hadfs mounts " << mounts << ", server " << server;

    return connect(mountRoot);
    //return connect(QDir("/home/sin/work/samba/ui/admc/mnt"));
}

void Connector::readStandardError()
{
    qDebug() << "ADFS stderror: " << adfs.readAllStandardError();
}

void Connector::readStandardOutput()
{
    qDebug() << "ADFS stdout: " << adfs.readAllStandardOutput();
}

bool Connector::lastErrorExists()
{
    QFileInfo lastErrorInfo(root, ".lasterror");
    //qDebug() << "lastErrorExists for: " << lastErrorInfo.filePath();
    return lastErrorInfo.exists();
}

QString Connector::lastError()
{
    return QFile(QFileInfo(root, ".lasterror").filePath()).readAll();
}

//QString Connector::lastError()
//{
//    QFileInfo lastErrorInfo(root, ".lasterror");

//    if (lastErrorInfo.exists() && lastErrorInfo.isFile() && lastErrorInfo.isReadable()) {
//        QFile lastErrorFile(lastErrorInfo.filePath());
//        return lastErrorFile.readAll();
//    } else {
//        qDebug() << "Connector::lastError file not exists or not readable: " << lastErrorInfo.filePath();
//        return QString("ADFS not found at ") + lastErrorInfo.path();
//    }
//}

bool Connector::connect(QDir mountpoint)
{
    root = mountpoint;

    if (mountpoint.isReadable())
    {
        int n = 20;
        while(n > 0)
        {
            if(lastErrorExists()) {
                qDebug() << "Connector::connect: " << mountpoint;
                return true;
            }
            QThread::msleep(500);
            qDebug() << "Connector::connect: waiting for connection: " << n--;
        }
    } else {
        qDebug() << "Connector::connect: not readable " << mountpoint;
        isUpdated = false;
    }

    return false;
}

void Connector::query(ObjectData &data, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::query: for null parent";
    } else {
        qDebug() << "Connector::query: " << parent->name();
    }
}

bool Connector::childs(LdapObjectList &objectList, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::childs: parent is null!";
        return false;
    }

    //qDeleteAll(objectList);

    QDir adfsPath(root.path() + QDir::separator() + parent->path());

    if (!adfsPath.isReadable()) {
        qDebug() << "Connector::childs: adfs path not ready" << adfsPath << QDir::currentPath();
        return false;
    }

    adfsPath.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "Connector::childs: adfs path is" << adfsPath;

    if (adfsPath.isEmpty()) {
        qDebug() << "Connector::childs: adfs path is empty";
    }

    QDirIterator it(adfsPath);
    while (it.hasNext()) {
        QString child = it.next();
        qDebug() << "Connector::childs: " << child;
        QFileInfo info(child);
        QFileInfo attributesInfo(child, ".attributes.json");
        //QFileInfo attributesInfoOld(child.replace("/mnt","/.cache-domain.alt"), ".attributes.json");
        if(info.isDir()) {
            //if (attributesInfoOld.exists())
            //    attributesInfo = attributesInfoOld;
            if (!attributesInfo.isFile() || !attributesInfo.isReadable()) {
                qDebug() << "Connector::child attribute file not exists or not readable: " << attributesInfo.filePath() << attributesInfo.isFile() << attributesInfo.isReadable();
                continue;
            }
            LdapObject *object = new LdapObject(info.fileName(), *this, parent);
            QFile attributesFile(attributesInfo.filePath());
            qDebug() << "Connector::childs0: " << attributesInfo.filePath();
            if (attributesFile.open(QIODevice::ReadOnly))
            {
                QByteArray attributesData = attributesFile.readAll();
                qDebug() << "Connector::childs1: " << attributesInfo.filePath();
                QJsonDocument attributesDocument(QJsonDocument::fromJson(attributesData));

                qDebug() << "Connector::childs2: " << attributesInfo.filePath();
                QJsonObject jsonObject = attributesDocument.object();
                if (jsonObject.contains("trDN") && jsonObject["trDN"].isString()) {
                    QString dn = jsonObject["trDN"].toString();

                    if (jsonObject.contains("trAttrs") && jsonObject["trAttrs"].isObject()) {
                        object->appendAttribute("dn", "ObjectDSDN", dn);
                        qDebug() << "attribute dn: " << dn;

                        QJsonObject jsonAttrs = jsonObject["trAttrs"].toObject();
                        foreach(const QString& key, jsonAttrs.keys()) {
                            if (!jsonAttrs[key].isArray())
                                continue;
                            QJsonArray attrArray = jsonAttrs[key].toArray();
                            if (!attrArray[0].isObject() || !attrArray[1].isArray())
                                continue;
                            QJsonObject attrTypeTag = attrArray[0].toObject();
                            QJsonArray attrValues = attrArray[1].toArray();
                            if (!attrTypeTag["tag"].isString() || !attrValues[0].isString())
                                continue;
                            QString value = attrValues[0].toString();
                            QString type = attrTypeTag["tag"].toString();
                            object->appendAttribute(key, type, value);
                            qDebug() << "attribute: " << key << type << value;
                        }
                    }
                }
            } else {
               qDebug() << "attribute not opened: " << attributesInfo.filePath();
            }
            objectList.append(object);
        } else {
            qDebug() << "Connector::child not dir: " << child;
        }
    }

    return true;
}

void Connector::queryRoot(ObjectData &data, LdapObjectList &objectList, LdapConnection *connection)
{
    if (!connection) {
        qDebug() << "Connector::query: for null connection";
    } else {
        qDebug() << "Connector::query: for connection" << connection->name();

        LdapObject *parent = connection;

        isUpdated = !childs(objectList, parent);
    }
}

bool Connector::updated() const
{
    return isUpdated;
}

QStringList Connector::search(QString server)
{
    QStringList mounts;
    QFile mtabFile("/proc/mounts");
    if (mtabFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&mtabFile);
        QRegularExpression mtabPattern("^(adfs|hadfs) (.*) fuse.(\\S*) ");
        qDebug() << "mtab opened: " << mtabFile.fileName();
        QString line = in.readLine();
        while (!line.isEmpty()) {
            QRegularExpressionMatch res = mtabPattern.match(line);
            //qDebug() << "mtab line: " << line;
            if (res.hasMatch()) {
                qDebug() << "mtab match: " << server << res.capturedTexts().at(2);
                if (server == res.capturedTexts().at(3))
                    mounts << res.capturedTexts().at(2);
                qDebug() << "mtab: " << res.capturedTexts();
                qDebug() << "mtab mounts: " << mounts << " for " << res.capturedTexts().at(3) << "(" << server << ")";
            }
            line = in.readLine();
        }
        mtabFile.close();
    } else {
        qDebug() << "mtab file not opened: " << mtabFile.errorString();
    }
    return mounts;
}
