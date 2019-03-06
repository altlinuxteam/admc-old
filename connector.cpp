#include "connector.h"
#include "ldapobject.h"
#include "ldapconnection.h"
#include "common.h"

#include <QDirIterator>

Connector::Connector(QObject *parent) : QObject(parent), isMounted(false), isUpdated(true)
{

}

bool Connector::connect(QString server)
{
    QStringList mounts = search(server);
    dc = server;
    qDebug() << "Connector::connect: mounts " << mounts << ", server " << server;
    if (!mounts.empty())
        return connect(QDir(mounts.at(0)));
    return connect(QDir("/home/sin/work/samba/ui/admc/mnt"));
}

bool Connector::connect(QDir mountpoint)
{
    root = mountpoint;

    if (mountpoint.isReadable())
    {
        qDebug() << "Connector::connect: " << mountpoint;
        isMounted = true;
        return true;
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

void Connector::childs(LdapObjectList &objectList, LdapObject *parent)
{
    if (!parent) {
        qDebug() << "Connector::childs: parent is null!";
        return;
    }

    //qDeleteAll(objectList);

    qDebug() << "Connector::childs: root path is" << root.path();
    QDir adfsPath(root.path() + QDir::separator() + parent->path());

    if (!adfsPath.isReadable()) {
        qDebug() << "Connector::childs: adfs path not ready" << adfsPath << QDir::currentPath();
        return;
    }

    adfsPath.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "Connector::childs: adfs path is" << adfsPath;

    QDirIterator it(adfsPath);
    while (it.hasNext()) {
        QString child = it.next();
        qDebug() << "Connector::childs: " << child;
        QFileInfo info(child);
        QFileInfo attributesInfo(child, ".attributes");
        if(info.isDir() && attributesInfo.isFile() && attributesInfo.isReadable()) {
            LdapObject *object = new LdapObject(info.fileName(), *this, parent);
            QFile attributesFile(attributesInfo.filePath());
            if (attributesFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&attributesFile);
               QRegularExpression attributePattern("^(\\S+): (.*)$");
               QRegularExpression attributeBase64Pattern("^(\\S+):: (.*)$");
               QRegularExpression commentPattern("^#");
               while (!in.atEnd())
               {
                  QString line = in.readLine();
                  QRegularExpressionMatch res = commentPattern.match(line);
                  if (res.hasMatch())
                      continue;
                  res = attributeBase64Pattern.match(line);
                  if (!res.hasMatch())
                     res = attributePattern.match(line);
                  if (res.hasMatch()) {
                     object->appendAttribute(res.captured(2), res.captured(1));
                     qDebug() << "attribute: " << res.capturedTexts();
                  }
               }
               attributesFile.close();
            } else {
               qDebug() << "attribute not opened: " << attributesInfo.path();
            }
            objectList.append(object);
        } else {
            qDebug() << "Connector::child not dir: " << child;
        }
    }
}

void Connector::queryRoot(ObjectData &data, LdapObjectList &objectList, LdapConnection *connection)
{
    if (!connection) {
        qDebug() << "Connector::query: for null connection";
    } else {
        qDebug() << "Connector::query: for connection" << connection->name();

        LdapObject *parent = connection;
        childs(objectList, parent);
        isUpdated = false;
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
            if (res.hasMatch()) {
                if (server.isNull() || server == res.capturedTexts().at(3))
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
